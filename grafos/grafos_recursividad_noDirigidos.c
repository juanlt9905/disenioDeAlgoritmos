#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARISTAS 25000
#define MAX_NODOS 3000

int aristas[MAX_ARISTAS][2];
int nodos_visitados[MAX_NODOS];
//int ciclo_encontrado = 0;

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

TNodo *sucesores(TNodo * nodo_actual, int numAristas){

    TNodo *sucesores=NULL;
    int valor_nodo=nodo_actual->info;

    for (int i=0; i<numAristas; i++){
        if (aristas[i][0]== valor_nodo) AgregarInicio(&sucesores, aristas[i][1], nodo_actual);
        else if (aristas[i][1]== valor_nodo) AgregarInicio(&sucesores, aristas[i][0], nodo_actual);
    }


    return sucesores;
}


int busquedaRecursiva(TNodo *nodo_actual, int numAristas, int padre_info) {

    nodos_visitados[nodo_actual->info]=1;

    //Obtenemos los sucesores del nodo actual e iteramos
    TNodo *lista_sucesores = sucesores(nodo_actual, numAristas);
    TNodo *sucesor_actual = lista_sucesores;
    while (sucesor_actual != NULL){
        if(sucesor_actual->info != padre_info){
            if (nodos_visitados[sucesor_actual->info]==1 || busquedaRecursiva(sucesor_actual, numAristas, nodo_actual->info)==1)
                return 1;
            }   
            //Avanzo al siguiente sucesor
        sucesor_actual=sucesor_actual->sig;
    }
    liberarLista(lista_sucesores);
    return 0; //aqui ya se exploro todos los sucesores de nodo_actual, si se llego a este punto,
                // nodo_actual no llega a ningun ciclo. Por lo tanto, 
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
    
    for (int i = 0; i < numNodos; i++) {
        nodos_visitados[i] = 0;
    }
    int ciclo=0;
    for (int i=0; i <numNodos; i++) { //Busqueda por cada nodo
        if (nodos_visitados[i] == 0) {
            TNodo *nodo_inicial = (TNodo*) malloc(sizeof(TNodo));
            nodo_inicial->info = i;
            nodo_inicial->padre = NULL;
            nodo_inicial->sig = NULL;
            
            if (busquedaRecursiva(nodo_inicial, numAristas, -1)==1){
                ciclo=1;
                break;
            }
            
            free(nodo_inicial);
        }
    }

    if(ciclo==1)
        printf("Se encontro un ciclo. \n");
    else
        printf("NO se encontro un ciclo.\n");

    return 0;
}





/*
    while (sucesor_actual != NULL){
        //verificar si el sucesor crea un ciclo
        // Ignorar al padre 
        if (sucesor_actual->info == padre_info){
            sucesor_actual = sucesor_actual->sig;
            continue; // continuamos con el siguente sucesor
        }
        // verificar si el sucesor ya fue visitado/
        if (nodos_visitados[sucesor_actual->info]==1){
            ciclo_encontrado = 1;
            break; 
        } 
        else {
            busquedaRecursiva(sucesor_actual, numAristas, nodo_actual->info);
        }
        // Si la bandera cambio en la llamada recursiva, detener el bucle
        if (ciclo_encontrado==1){
            break;
        }
        sucesor_actual=sucesor_actual->sig;
    }
 */