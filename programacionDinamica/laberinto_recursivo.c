#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAX 10
char laberinto[MAX][MAX];
int soluciones[MAX+1][MAX+1];
char camino[MAX];

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return b > a ? a : b; }
/*
int labRecursivo(int i, int j, int renglones, int columnas){
 
    printf("Llamada para %d, %d\n", i,j);
    if (soluciones[i][j] == -100 || (i == renglones-1 && j == columnas-1)) 
        return soluciones[i][j]; //valores ya almacenados en soluciones.
    else if(i==renglones-1 && j!= columnas-1){
        soluciones[i][j] = soluciones[i][j] + labRecursivo(i, j+1, renglones, columnas);
    }else if (j==columnas-1){
        soluciones[i][j] = soluciones[i][j] +labRecursivo(i+1, j, renglones, columnas); 
    }else{
        soluciones[i][j]= soluciones[i][j] + max(labRecursivo(i+1, j, renglones, columnas),labRecursivo(i, j+1, renglones, columnas));
    }
    return soluciones[i][j];

}*/

int labRecursivo(int i, int j, int renglones, int columnas){

    //int down = labRecursivo(i+1, j, renglones,columnas);
    //int right = labRecursivo(i, j+1, renglones, columnas);
      
    //caso de obstaculo
    if (laberinto[i][j] == '#') 
        return soluciones[i][j] = -100;
    if (i==renglones-1 && j== columnas-1){//caso base para la meta
        if(laberinto[i][j]== 'o'){
            return soluciones[i][j]= 1;
        }else return soluciones[i][j]=0;
    }
    if (soluciones[i][j]!=-200) return soluciones[i][j];
    if (i ==renglones-1){
        if(laberinto[i][j]=='o') soluciones[i][j] = 1+labRecursivo(i, j+1, renglones, columnas);
        else soluciones[i][j] = labRecursivo(i, j+1, renglones, columnas);
    }
    else if (j ==columnas-1){
        if(laberinto[i][j]=='o') soluciones[i][j] = 1+labRecursivo(i+1, j, renglones, columnas);
        else soluciones[i][j] = labRecursivo(i+1, j, renglones, columnas);
    }
    else{
        if(laberinto[i][j]=='o') soluciones[i][j] = 1+ max(labRecursivo(i+1, j, renglones, columnas), labRecursivo(i, j+1, renglones, columnas));
        else soluciones[i][j] = max(labRecursivo(i+1, j, renglones, columnas), labRecursivo(i, j+1, renglones, columnas));
    }
    return soluciones[i][j];


}



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
                soluciones[i][j]=-200;
            }
            else
                soluciones[i][j]=-100;

        }
    }

    printf("Soluciones Inicializada: \n");
    for (int i = 0; i <=renglones; i++) {
        for (int j = 0; j <= columnas; j++) {
            printf("%d ", soluciones[i][j]);
        }
        printf("\n");
    }


    // Primera ejecucion recursiva
    labRecursivo(0, 0, renglones, columnas);

    
    printf("Matriz de soluciones:\n");
    for (int i = 0; i < renglones; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", soluciones[i][j]);
        }
        printf("\n");
    }
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

    printf("\n");

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




