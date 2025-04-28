#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define MAX 1000

int max(int a, int b) { return a > b ? a : b; }
int lcss(char *a, char *b, int i, int j, int memoria[MAX][MAX]){

    if (a[i] == '\0' || b[j] == '\0')return 0;
    if (memoria[i][j] != -1)return memoria[i][j];
    if (a[i] == b[j])
        memoria[i][j] = 1 + lcss(a, b, i+1, j+1, memoria);
    else
        memoria[i][j] = max(lcss(a, b, i+1, j, memoria), lcss(a, b, i, j+1, memoria));
    return memoria[i][j];


}


int main(int argc, char **argv){

    char *a = argv[1];
    char *b = argv[2];

    int lenA = strlen(a);
    int lenB = strlen(b);

    //el elemento memoria[i][j] almacenara el valor de lccs para la subcadena 
    //a[i:] y b[j:]
    int memoria[MAX][MAX];

    // Inicializamos la matriz memoria con valores de -1
    for (int i = 0; i < MAX; ++i){
        for (int j = 0; j < MAX; ++j){
            memoria[i][j] = -1;
        }
    }

    int x = lcss(a,b,0,0, memoria);

    printf("La longitud maxima de la cadena comun es: %d\n", x);
    
    return 0;
}