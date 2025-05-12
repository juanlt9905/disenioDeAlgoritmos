#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAXIMO 1000
char a[MAXIMO];
char b[MAXIMO];
int matriz[MAXIMO][MAXIMO];

int max(int a, int b) { return a > b ? a : b; }
int main(int argc, char **argv){


    //Cadenas de entrada
    char *a = argv[1];
    char *b = argv[2];

    int lenA =strlen(a);
    int lenB=strlen(b);

    
    for (int i = 0; i<=lenA; i++){
        for (int j= 0; j<=lenB; j++){
            matriz[i][j] =0 ;
        }
    }
    
    //Llenar la matriz de arriba hacia abajo
    /*for (int i = 0; a[i]!='\0'; i++){
        for (int j= 0; b[j]!='\0'; j++){
            if(a[i]==b[j])
                matriz[i+1][j+1]= 1 + matriz[i][j]; 
            else
                matriz[i+1][j+1]=max(matriz[i][j+1], matriz[i+1][j]);
        }

    }*/

    // Llenar la matriz de abajo hacia arriba
    for (int i= lenA-1; i>=0; i--) {
        for (int j = lenB-1; j>= 0; j--) {
            if (a[i] == b[j]) {
                matriz[i][j] = 1 + matriz[i+1][j+1];
            } else {
                matriz[i][j] = max(matriz[i+1][j], matriz[i][j+1]);
            }
        }
    }
    

    int resultado = matriz[0][0];
    printf("Resultado: %d\n", resultado);






    return 0;
}