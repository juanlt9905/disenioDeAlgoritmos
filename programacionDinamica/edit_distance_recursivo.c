#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAXIMO 1000
char a[MAXIMO];
char b[MAXIMO];
int matriz[MAXIMO][MAXIMO];
//int banderas[MAXIMO][MAXIMO];
#define sin_calcular -1;


int minimo_tres_num(int a, int b, int c) {
    int minimo=a;
    if (b<minimo) {
        minimo=b;
    }
    if (c< minimo) {
        minimo=c;
    }
    return minimo;
}

int ED(char *a, char *b, int i, int j, int lenA, int lenB){


    //Casos base (comparaciones con cadena vacia)
    if (i== lenA) {
        return lenB-j;
    }

    if (j==lenB) {
        return lenA-i;
    }
    if (matriz[i][j]!=-1) return matriz[i][j]; //
    
    int resultado;

    if (a[i]== b[j]) { //caracteres iguales, nos movemos en diagonal
        resultado = ED(a, b, i + 1, j + 1, lenA, lenB);
    } else {
        //borrado(avanza en a)
        int costo_borrar = ED(a, b, i+1, j, lenA, lenB);
        //insertar(avanzar en b)
        int costo_insertar = ED(a, b, i, j+1, lenA, lenB);
        //sustitucioon (avanzar en ambas)
        int costo_sustitucion = ED(a, b, i+1, j+1, lenA, lenB);

        resultado = 1 + minimo_tres_num(costo_borrar, costo_insertar, costo_sustitucion);
    }

    matriz[i][j] =resultado;



    return resultado;

}
int main(int argc, char **argv){

    char *a = argv[1];
    char *b = argv[2];

    int lenA = strlen(a);
    int lenB = strlen(b);

    //Inicializar matriz que lleva registro de los subproblemas calculados

    for (int i = 0; i < lenA; ++i){
        for (int j = 0; j < lenB; ++j){
            matriz[i][j] = sin_calcular;
        }
    }

    int distancia = ED(a,b,0,0, lenA, lenB);

    printf("Distancia de edición: %d\n", distancia);


    return 0;
}