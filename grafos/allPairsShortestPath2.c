#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>

#define MAX_ARISTAS 25000
#define MAX_NODOS 2000
#define inf 1000


typedef struct nodo{
    int info;
    struct nodo *sig;
}TNodo;


typedef struct {
    int u;
    int v;
    int peso;
}Arista;

Arista aristas[MAX_ARISTAS]; //arreglo de estructuras tipo aristas


int matriz_costos[MAX_NODOS][MAX_NODOS];
int matriz_padres[MAX_NODOS][MAX_NODOS];


int obtenerPeso(int u, int v, int numAristas) {
    //iteramos sobre aristas
    for (int i=0; i<numAristas; i++) {
        if (aristas[i].u== u && aristas[i].v == v) {
            return aristas[i].peso;
        }
    }
    return -1; // no se encontro arista
}

void AgregarInicio(TNodo**lista, int dato){
    TNodo *nuevo=NULL;
    //Agregar memoria para el nuevo nodo
    nuevo=(TNodo*) malloc(sizeof(TNodo));
    nuevo->info=dato; //Asigna el valor a nodo
    nuevo->sig= *lista; //Coloca nodo al inicio de lista
    *lista = nuevo; //El inicio de lista cambia al nuevo
}



TNodo *sucesores(TNodo *nodo_actual, int numAristas) {
    TNodo *lista_sucesores = NULL;
    int valor_nodo = nodo_actual->info;
    for (int i = 0; i < numAristas; i++) {
        if (aristas[i].u == valor_nodo) {
            AgregarInicio(&lista_sucesores, aristas[i].v);
        }
    }
    return lista_sucesores;
}

void inicializar_matrices(int numNodos, int numAristas){
    
    for (int i = 0; i < numNodos; i++) {
        for (int j = 0; j < numNodos; j++) {
            if (i == j) {
                matriz_costos[i][j] = 0;
            } else {
                matriz_costos[i][j] = inf;
            }
            matriz_padres[i][j] = -1; // -1 significa sin predecesor conocido
        }
    }
     //asignacion de pesos y padre a las aristas adyacentes
    for (int i = 0; i < numAristas; i++) {
        int u = aristas[i].u;
        int v = aristas[i].v;
        int peso = aristas[i].peso;

        matriz_costos[u][v] = peso;
        matriz_padres[u][v] = u;
    }
}


int main(int argc, char *argv[]){


    const char *inputfile = argv[1];

    FILE *file = fopen(inputfile, "r");
    int numAristas, numNodos;
    fscanf(file, "%d", &numNodos); // nodos de 0 a numNodos-1.
    fscanf(file, "%d", &numAristas);

    //almacenar las aristas en la matriz aristas[][]
    for(int i=0; i<numAristas; i++){
        fscanf(file, "%d %d %d", &aristas[i].u, &aristas[i].v, &aristas[i].peso);
    }
    
    fclose(file); 


    struct timeval inicio, fin;
    double tiempo_transcurrido;
    gettimeofday(&inicio, NULL);

    inicializar_matrices(numNodos, numAristas);

    //Bucle principal



    for (int k=0; k<numNodos; k++) { ///nodos intermedios
        for (int i = 0; i < numNodos; i++){ //iteracion sobre nodo inicial
            for (int j = 0; j < numNodos; j++) {//iteracion sobre nodo destino
               
                if (matriz_costos[i][k] + matriz_costos[k][j] < matriz_costos[i][j]) {
                    
                    matriz_costos[i][j] = matriz_costos[i][k] + matriz_costos[k][j];
                    matriz_padres[i][j] = matriz_padres[k][j];
                }
            }
        }
    }


    gettimeofday(&fin, NULL);

    long segundos = fin.tv_sec - inicio.tv_sec;
    long microsegundos = fin.tv_usec - inicio.tv_usec;
    tiempo_transcurrido = segundos + microsegundos * 1e-6;

    printf("%.6f", tiempo_transcurrido);

    /*printf("Matriz de costos\n");
    for (int i= 0; i < numNodos; i++){
        for (int j=0; j < numNodos; j++){
            printf("%d ", matriz_costos[i][j]);
        }
        printf("\n");
    }*/
    
    //printf("Padres single-source 2: \n");
    //for (int i=0; i<numNodos; i++){
    //    printf("%d ", padre[i]);    
    //}






    return 0;
}