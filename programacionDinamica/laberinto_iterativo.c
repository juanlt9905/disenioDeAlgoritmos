#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAX 100
char laberinto[MAX][MAX];
int soluciones[MAX+1][MAX+1];
char camino[MAX];

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return b > a ? a : b; }
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
    /*inicializamos la matriz soluciones, con 1 si hay un tesoro en laberinto,  -100 si hay un
    obstaculo o es el limite del laberinto, y 0 en los demas casos
    */

    for (int i=0; i<= renglones; i++) {
        for (int j=0; j <=columnas; j++) {
            if (i <renglones && j< columnas){
                if(laberinto[i][j]=='o')
                    soluciones[i][j]=1;
                else if (laberinto[i][j]=='#')
                    soluciones[i][j]=-100;
                else
                    soluciones[i][j]=0;
            }
            else
                soluciones[i][j]=-100;

        }
    }
    /*
    for (int i=0; i<= renglones; i++) {
        for (int j=0; j <=columnas; j++) {
            printf("%d ", soluciones[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */

    for (int i=renglones-1; i>=0; i--){
        for (int j=columnas-1; j>=0; j--){//se calcula la solucion para celdas que no son obstaculo y no son la celda meta
            if(laberinto[i][j]!='#' && (i!=renglones-1 || j!=columnas-1)){
                soluciones[i][j] = soluciones[i][j] + max(soluciones[i+1][j], soluciones[i][j+1]);
            }
        }
    }

    printf("Matriz de soluciones: \n");
    for (int i=0; i< renglones; i++) {
        for (int j=0; j <columnas; j++) {
            printf("%d ", soluciones[i][j]);
        }
        printf("\n");
    }

    //Calculo de ruta usando la matriz solucion, que se movera hacia la celda de mayor valor(abajo o derecha)

    int i=0, j=0, k=0;

    while( i!=renglones-1 || j!= columnas-1){
        if (i==renglones-1){
            j++;
            camino[k]='R'; //movimiento a la derecha
            k++;
        }
        else if (j==columnas-1){
            i++;
            camino[k]='D'; //movimiento hacia abajo
            k++;
        }
        else if (soluciones[i+1][j]>=soluciones[i][j+1]){
            i++;
            camino[k]= 'D'; //guardo un movimiento hacia abajo
            k++;
        }
        else{ 
            j++;
            camino[k]='R'; //guardo un movimiento a la derecha
            k++;
        }
    }
    camino[k] = '\0';

    if (soluciones[0][0]<0 ){
        printf("No hay camino a la meta\n");
    }else{
        printf("Ruta optima: \n");

        for (int i = 0; i< strlen(camino); i++){
            printf("%c ", camino[i]);
        }
        printf("\n");
    }

    return 0;
}

















    /*//Examinamos el laberinto y completamos soluciones
    for (int i=renglones-1; i>=0; i--){
        for (int j= columnas-1; j>=0; j--){
            if (laberinto[i][j]!= '#'){
                if (laberinto[i+1][j]!= '#' && laberinto[i][j+1]!= '#'){
                    soluciones[i][j] = soluciones[i][j] + max(soluciones[i][j+1], soluciones[i+1][j]);
                }
                else if (laberinto[i+1][j]=='#' && laberinto[i][j+1]!= '#'){
                    soluciones[i][j] = soluciones[i][j] + soluciones[i][j+1];
                }
                else if (laberinto[i][j+1]=='#' && laberinto[i+1][j]!= '#'){
                    soluciones[i][j]= soluciones[i][j] + soluciones[i+1][j];
                }
            }else
                soluciones[i][j]=min(soluciones[i][j], 0);
        }
    }*/