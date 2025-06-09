#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARISTAS 100
#define MAX_NODOS 100

int aristas[MAX_ARISTAS][2];
int nodos_visitados[MAX_NODOS];
int enCamino[MAX_NODOS];
int ciclo_encontrado = 0;

typedef struct nodo {
    int info;
    struct nodo *sig;
    struct nodo *padre;
} TNodo;

void AgregarInicio(TNodo **lista, int dato, TNodo *padre) {
    TNodo *nuevo = (TNodo *)malloc(sizeof(TNodo));
    nuevo->info = dato;
    nuevo->padre = padre;
    nuevo->sig = *lista;
    *lista = nuevo;
}

void liberarLista(TNodo *lista) {
    TNodo *temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->sig;
        free(temp);
    }
}

TNodo *sucesores(TNodo *nodo_actual, int numAristas) {
    TNodo *lista_sucesores = NULL;
    int valor_nodo = nodo_actual->info;
    for (int i = 0; i < numAristas; i++) {
        if (aristas[i][0] == valor_nodo) {
            AgregarInicio(&lista_sucesores, aristas[i][1], nodo_actual);
        }
    }
    return lista_sucesores;
}

void busquedaRecursiva(TNodo *nodo_actual, int numAristas) {
    // Si ya se encontró un ciclo en otra parte del grafo, detener la ejecución.
    if (ciclo_encontrado==1){
        return;
    }

    nodos_visitados[nodo_actual->info]=1;
    enCamino[nodo_actual->info] = 1;

    //Obtenemos los sucesores del nodo actual e iteramos
    TNodo *lista_sucesores = sucesores(nodo_actual, numAristas);
    TNodo *sucesor_actual = lista_sucesores;
    while (sucesor_actual != NULL) {
        //verificar si el sucesor crea un ciclo
        if (enCamino[sucesor_actual->info] == 1) {
            //se detecta un ciclo
            ciclo_encontrado = 1;
            liberarLista(lista_sucesores); 
            return; 
        }
        else if (nodos_visitados[sucesor_actual->info]== 0) {
            busquedaRecursiva(sucesor_actual, numAristas);
        }
        // Si la bandera cambio en la llamada recursiva, detener el bucle
        if (ciclo_encontrado==1){
            break;
        }
        sucesor_actual=sucesor_actual->sig;
    }
    liberarLista(lista_sucesores);
    //Backtraking. Se elimina nodo del camino si todos sus hijos ya fueron explorados y no se encontr un ciclo
    enCamino[nodo_actual->info]=0;
}

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

    // Bandera y arreglos de registro de nodos visitados y camino
    ciclo_encontrado = 0;
    for (int i = 0; i < numNodos; i++) {
        nodos_visitados[i] = 0;
        enCamino[i] = 0;
    }

    for (int i=0; i <numNodos; i++) { //Busqueda por cada nodo
        if (nodos_visitados[i] == 0) {
            TNodo *nodo_inicial = (TNodo*) malloc(sizeof(TNodo));
            nodo_inicial->info = i;
            nodo_inicial->padre = NULL;
            nodo_inicial->sig = NULL;
            
            busquedaRecursiva(nodo_inicial, numAristas);
            
            free(nodo_inicial);
        }
        
        // si en alguna iteración se encontro un ciclo, detenemos la busqueda.
        if (ciclo_encontrado==1) {
            break;
        }
    }

    if(ciclo_encontrado==1)
        printf("Se encontro un ciclo. \n");
    else
        printf("NO se encontro un ciclo.\n");




    return 0;
}