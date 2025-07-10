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
int padre[MAX_NODOS];
int costo[MAX_NODOS];
int nodosProcesados[MAX_NODOS]={0};

int matriz_costos[MAX_NODOS][MAX_NODOS];
int matriz_padres[MAX_NODOS][MAX_NODOS];

//HEAP


typedef struct {
    int elementos[MAX_NODOS]; // 
    int posicionEnHeap[MAX_NODOS]; 
    int nElementos;
} MinHeap;
 
// FUNCIONES DEL MIN-HEAP

void inicializarMinHeap(MinHeap * heap){
    heap->nElementos = 0;
    for(int i = 0; i < MAX_NODOS; i++){
        heap->posicionEnHeap[i] = -1; // no esta en el heap
    }
}

void swap(MinHeap* heap, int pos1, int pos2) { //intercambio de elementos en el heap
    int temp =heap->elementos[pos1];
    heap->elementos[pos1] =heap->elementos[pos2];
    heap->elementos[pos2] =temp;
    
    // actualiza posiciones
    heap->posicionEnHeap[heap->elementos[pos1]]= pos1;
    heap->posicionEnHeap[heap->elementos[pos2]]= pos2;
}

//subir un elemento desde una posicion especifica
void bubbleUp(MinHeap* heap, int pos){
    while(pos > 0){
        int padre = (pos - 1) / 2;
        if(costo[heap->elementos[pos]] <costo[heap->elementos[padre]]){
            swap(heap, pos, padre);
            pos = padre;
        } else {
            break;
        }
    }
}
//bajar un elemento desde una posicion especifica
void bubbleDown(MinHeap* heap, int pos){
    while(1){
        int hijoIzq=2*pos+1;
        int hijoDer=2*pos+2;
        int menor=pos;

        if(hijoIzq < heap->nElementos && 
           costo[heap->elementos[hijoIzq]]<costo[heap->elementos[menor]])
            menor = hijoIzq;
            
        if(hijoDer < heap->nElementos && 
           costo[heap->elementos[hijoDer]] <costo[heap->elementos[menor]])
            menor = hijoDer;

        if(menor !=pos){
            swap(heap, pos, menor);
            pos = menor;
        } else {
            break;
        }
    }
}

void insertarElementoMinHeap(MinHeap * heap, int nodo){
    if (heap->nElementos>= MAX_NODOS){
        printf("Heap lleno\n");
        return;
    }

    int pos =heap->nElementos++;
    heap->elementos[pos] = nodo;
    heap->posicionEnHeap[nodo] =pos;
    
    bubbleUp(heap, pos);
}

int extraerMin(MinHeap * heap){
    if (heap->nElementos == 0) {
        printf("Heap vacio\n");
        return -1;
    }

    int minNodo = heap->elementos[0];
    heap->posicionEnHeap[minNodo]=-1; //quitarlo del heap
    
    //mover el ultimo elemento del heap al inicio
    heap->elementos[0] = heap->elementos[heap->nElementos - 1];
    heap->posicionEnHeap[heap->elementos[0]] = 0;
    heap->nElementos--;
    
    //reubicar el elemento del inicio
    if(heap->nElementos > 0){
        bubbleDown(heap, 0);
    }
    
    return minNodo;
}

void decreaseKey(MinHeap* heap, int nodo, int nuevoCosto){
    if(heap->posicionEnHeap[nodo]==-1){
        return; //el nodo no esta en el heaap
    }
    
    if(nuevoCosto >= costo[nodo]){
        return; //verificar que el nuevo costo si sea menor al anterior
    }
    costo[nodo] = nuevoCosto;
    
    //subir el elemento de nueva prioridad
    bubbleUp(heap, heap->posicionEnHeap[nodo]);
}



void inicializar_fuente(int fuente, int numNodos){
    for (int i=0; i<numNodos; i++){
        padre[i]=-1;
        costo[i]= inf;
    }
    padre[fuente]=-1;
    costo[fuente]=0;
}

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

void relaxation(int u, int v, int peso, MinHeap *heap){
    if (costo[v]>costo[u]+peso){
        //costo[v] =costo[u]+peso;
        assert(u >= 0 && u < MAX_NODOS);
        assert(v >= 0 && v < MAX_NODOS);
        padre[v] =u;
        decreaseKey(heap, v, costo[u]+peso);
    }
}

void verTodos(TNodo*lista){ //Muestra todos los nodos de la lista

    while(lista!=NULL){
        printf("%d ", lista->info);

        lista=lista->sig;

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


    //Bucle que itera sobre todos los nodos, como nodos fuente
    for (int i=0; i<numNodos; i++){
        MinHeap Q;
        inicializarMinHeap(&Q);
        inicializar_fuente(i, numNodos);


        for (int j=0; j<numNodos; j++){
            insertarElementoMinHeap(&Q, j);
        }


        while(Q.nElementos>0){
            int u =extraerMin(&Q);
            nodosProcesados[u]=1;


            //sucesores
            for (int k=0; k<numAristas; k++){
                if (aristas[k].u==u){
                    int v=aristas[k].v;

                    //assert(u >= 0 && u < numNodos);
                    //assert(v >= 0 && v < numNodos);
                    relaxation(u,v,aristas[k].peso, &Q);
                }
            }

        }
    
        //Crear matrices
        for (int j=0; j<numNodos;j++){
            matriz_costos[i][j]=costo[j];
            matriz_padres[i][j]=padre[j];
        }
    }

    printf("Matriz de costos\n");
    for (int i= 0; i < numNodos; i++){
        for (int j=0; j < numNodos; j++){
            printf("%d ", matriz_costos[i][j]);
        }
        printf("\n");
    }
    
    //printf("Padres single-source 2: \n");
    //for (int i=0; i<numNodos; i++){
    //    printf("%d ", padre[i]);    
    //}






    return 0;
}