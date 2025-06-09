#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAX 100
#define MAX_NODOS 100 

int aristas[MAX][2];
int nodos_visitados[MAX_NODOS];
int enCamino[MAX_NODOS];

typedef struct nodo{
    int info;
    struct nodo * sig;
    struct nodo * padre;
}TNodo;

void AgregarInicio(TNodo**lista, int dato, TNodo *padre){
    TNodo *nuevo = (TNodo*) malloc(sizeof(TNodo));
    nuevo->info = dato;
    nuevo->padre = padre;
    nuevo->sig = *lista;
    *lista = nuevo;
}

void VerTodos(TNodo*lista){
    while(lista != NULL){
        printf("%d ", lista->info);
        lista = lista->sig;
    }
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
    TNodo *sucesores = NULL;
    int valor_nodo = nodo_actual->info;

    // Agregando los sucesores de nodo_actual a la lista
    for (int i = 0; i < numAristas; i++){
        if (aristas[i][0] == valor_nodo) {
            AgregarInicio(&sucesores, aristas[i][1], nodo_actual);
        }
    }
    return sucesores;
}


//version sin funcion de backtrack que recorre hasta la raiz
int busquedaPorProfundidad2(int nodo_inicio, int numAristas){
    printf("---Busqueda Iniciada para nodo: %d ---\n", nodo_inicio);
    
    TNodo *abiertos = NULL;
    int camino_local[MAX_NODOS] = {0};
    
    AgregarInicio(&abiertos, nodo_inicio, NULL);
    
    while(abiertos != NULL){
        TNodo *actual = abiertos;
        abiertos = abiertos->sig;
        
        int valor = actual->info;
        
        // Si ya está en el camino actual, hay ciclo
        if(camino_local[valor] == 1){
            //ciclo encontrado
            return 1;
        }
        
        // Si ya fue visitado globalmente, omitir
        if(nodos_visitados[valor] == 1){
            continue;
        }
        
        // Marcar en camino actual
        camino_local[valor] = 1;
        
        //generar sucesores
        TNodo *sucesores_lista = sucesores(actual, numAristas);
        TNodo *temp = sucesores_lista;
        
        int tiene_sucesores = 0;
        while(temp != NULL){
            if(camino_local[temp->info] == 1){
                liberarLista(sucesores_lista);
                return 1;
            }
            
            if(nodos_visitados[temp->info] == 0){
                AgregarInicio(&abiertos, temp->info, actual);
                tiene_sucesores = 1;
            }
            temp=temp->sig;
        }
        
        if(!tiene_sucesores){
            //nodo hoja, marcar como visitado
            nodos_visitados[valor] = 1;
            camino_local[valor] = 0;
        }
        
        liberarLista(sucesores_lista);
        free(actual);
    }
    
    return 0;
}

int main(){
    FILE *file = fopen("grafo.txt", "r");
    
    int numAristas, numNodos;
    fscanf(file, "%d", &numNodos);
    fscanf(file, "%d", &numAristas);

    //printf("Nodos: %d, Aristas: %d\n", numNodos, numAristas);

    for(int i = 0; i < numAristas; i++){
        fscanf(file, "%d %d", &aristas[i][0], &aristas[i][1]);
        //printf("Arista: %d -> %d\n", aristas[i][0], aristas[i][1]);
    }
    fclose(file);

    // Inicialización
    for(int i = 0; i < numNodos; i++){
        nodos_visitados[i] = 0;
        enCamino[i] = 0;
    }

    int ciclo_grafo = 0;
    
    //probar desde cada nodo no visitado
    for(int i = 0; i < numNodos; i++){
        if(nodos_visitados[i] == 0){
            //resetear enCamino para nueva busqueda
            for(int j = 0; j < numNodos; j++){
                enCamino[j] = 0;
            }
            
            if(busquedaPorProfundidad2(i, numAristas) == 1){
                ciclo_grafo = 1;
                break;
            }
        }
    }

    if(ciclo_grafo == 1)
        printf("Se encontro un cilco en el grafo. \n");
    else
        printf("NO se encontro un cilco en el grafo. \n");

    return 0;
}