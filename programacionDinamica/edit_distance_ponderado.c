#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAXIMO 1000
char a[MAXIMO];
char b[MAXIMO];
int matriz[MAXIMO][MAXIMO];

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

int main(int argc, char **argv){

    //Cadenas de entrada
    char *a = argv[1];
    char *b = argv[2];
    int ponderacion_sustituir = 2;//atoi(argv[3]);
    int ponderacion_borrar = 1;//atoi(argv[4]);
    int ponderacion_insertar = 4;//atoi(argv[5]);

    int lenA =strlen(a);
    int lenB=strlen(b);
    
    // Inicialización de los casos base (contra cadena vacia)
    for (int i = lenA; i >= 0; i--) {
        matriz[i][lenB] = lenA - i; 
    }

    for (int j = lenB; j >= 0; j--) {
        matriz[lenA][j] = lenB - j; 
    }


    
    // Llenar la matriz de abajo hacia arriba
    for (int i= lenA-1; i>=0; i--) {
        for (int j = lenB-1; j>= 0; j--) {
            if (a[i] == b[j]) {
                matriz[i][j] = matriz[i + 1][j + 1]; // Sin coste si los caracteres coinciden
            } else {
                matriz[i][j] =minimo_tres_num( ponderacion_insertar+ matriz[i+1][j],
                                                ponderacion_borrar +matriz[i][j+1], 
                                                ponderacion_sustituir +matriz[i+1][j+1]);
        }
    }
    }

    //Imprimir matriz de resultado

    printf("Matriz de resultados: \n");
    for (int i = 0; i<=lenA; i++){
        for (int j= 0; j<=lenB; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("ED: %d\n", matriz[0][0]);

    

    return 0; 
}