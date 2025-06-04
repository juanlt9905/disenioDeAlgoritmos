#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAX 100
#define MAX_NODOS 100 
int aristas[MAX][2];
int nodos_visitados[MAX_NODOS];

int main(){

    FILE *file = fopen("grafo.txt", "r");
    int numAristas, numNodos;
    fscanf(file, "%d", &numNodos); // nodos de 0 a numNodos-1.
    fscanf(file, "%d", &numAristas);

    //almacenar las aristas en la matriz aristas[][]
    for(int i=0; i<numAristas; i++){
        for(int j=0; j<2; j++)
            fscanf(file, "%d", &aristas[i][j]);
    }

    fclose(file); 
    //inicializacion de nodos visitados.
    for (int i=0; i<numNodos; i++) 
        nodos_visitados[i] = 0;

    for (int i=0; i<numAristas; i++){
        if (aristas[i][0]== valor_nodo) AgregarInicio(&sucesores, aristas[i][1], nodo_actual);
    }





    return 0;
}