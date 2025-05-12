#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#define MAX 100
char laberinto[MAX][MAX];
int soluciones[MAX][MAX];

int max(int a, int b) { return a > b ? a : b; }

int main(){

    // Abrir el archivo de entrada
    FILE *file = fopen("laberinto.txt", "r");

    int renglones, columnas;
    fscanf(file, "%d %d", &renglones, &columnas);

    // Leer el laberinto y llenar la matriz
    for (int i = 0; i < renglones; i++) {
        for (int j = 0; j < columnas; j++) {
            fscanf(file, " %c", &laberinto[i][j]); // ' %c' para ignorar espacios
        }
    }
    fclose(file);
    //inicializamos la matriz soluciones, con 1 si hay un tesoro en laberinto, y 0 los demas casos
    for (int i=0; i<= renglones; i++) {
        for (int j=0; j <=columnas; j++) {
            if (i <renglones && j<columnas && laberinto[i][j]== 'o') {
                soluciones[i][j] = 1;
            } else {
                soluciones[i][j] = 0;
            }
        }
    }
    //Examinamos el laberinto y completamos soluciones
    for (int i=renglones-1; i>=0; i--){
        for (int j= columnas-1; j>=0; j--){
            if (laberinto[i+1][j]!= '#' && laberinto[i][j+1]!= '#'){
                soluciones[i][j] = soluciones[i][j] + max(soluciones[i][j+1], soluciones[i+1][j]);
            }
            else if (laberinto[i+1][j]=='#' && laberinto[i][j+1]!= '#'){
                soluciones[i][j] = soluciones[i][j] + soluciones[i][j+1];
            }
            else if (laberinto[i][j+1]=='#' && laberinto[i+1][j]!= '#'){
                soluciones[i][j]= soluciones[i][j] + soluciones[i+1][j];
            }
        }
    }




    return 0;
}