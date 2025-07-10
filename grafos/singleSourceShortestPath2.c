#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_ARISTAS 25000
#define MAX_NODOS 3000
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
    int s=atoi(argv[2]);

    FILE *file = fopen(inputfile, "r");
    int numAristas, numNodos;
    fscanf(file, "%d", &numNodos); // nodos de 0 a numNodos-1.
    fscanf(file, "%d", &numAristas);

    //almacenar las aristas en la matriz aristas[][]
    for(int i=0; i<numAristas; i++){
        fscanf(file, "%d %d %d", &aristas[i].u, &aristas[i].v, &aristas[i].peso);
    }
    
    fclose(file); 

    MinHeap Q;
    inicializarMinHeap(&Q);

    //int s=1;
    inicializar_fuente(s, numNodos);



    for (int i=0; i<numNodos; i++){
        insertarElementoMinHeap(&Q, i);
    }


    struct timeval inicio, fin;
    double tiempo_transcurrido;
    gettimeofday(&inicio, NULL);
    while(Q.nElementos>0){
        int u =extraerMin(&Q);
        nodosProcesados[u]=1;

        //sucesores
        for (int i=0; i<numAristas; i++){
            if (aristas[i].u==u){
                int v=aristas[i].v;
                if(nodosProcesados[v]==0){
                    relaxation(u,v,aristas[i].peso, &Q);
                }
            }
        }

    }

    /*printf("Padres single-source 2: \n");
    for (int i=0; i<numNodos; i++){
        printf("%d ", padre[i]);    
    }

    printf("\n Costos: \n");
    for(int i=0; i<numNodos; i++){
        printf("%d ", costo[i]);
    }*/

    gettimeofday(&fin, NULL);
    printf("Padres single-source1: \n");
    for (int i=0; i<numNodos; i++){
        printf("%d ", padre[i]);    
    }

    printf("\n Costos: \n");
    for(int i=0; i<numNodos; i++){
        printf("%d ", costo[i]);
    }

    long segundos = fin.tv_sec - inicio.tv_sec;
    long microsegundos = fin.tv_usec - inicio.tv_usec;
    tiempo_transcurrido = segundos + microsegundos * 1e-6;

          // --- Generación de archivos de visualización ---
    char dot_filename[256];
    char png_filename[256];
    char command[1024];
    char numero_str[100];

    // Forma segura de extraer el número (ej. "500") del nombre del archivo de entrada
    // Primero, hacemos una copia para no modificar el original
    strncpy(numero_str, inputfile, sizeof(numero_str) - 1);
    numero_str[sizeof(numero_str) - 1] = '\0'; // Asegurar que la cadena termina en nulo

    // Buscamos la última '_' para encontrar dónde empieza el número
    char* parte_numerica = strrchr(numero_str, '_');
    if (parte_numerica != NULL) {
        // Si encontramos '_', movemos el puntero un caracter adelante
        parte_numerica++; 
    } else {
        // Si no hay '_', usamos el nombre completo como fallback
        parte_numerica = numero_str;
    }
    
    // Quitamos la extensión ".txt" si existe
    char* punto_ext = strrchr(parte_numerica, '.');
    if (punto_ext != NULL) {
        *punto_ext = '\0'; // Cortamos la cadena en el punto
    }
    // Ahora 'parte_numerica' contiene solo el número, ej: "500"

    // CORRECCIÓN: Usamos snprintf con la sintaxis correcta (destino, tamaño, formato, variable)
    snprintf(dot_filename, sizeof(dot_filename), "singleSourceScale/singleSource2_%s.dot", parte_numerica);
    snprintf(png_filename, sizeof(png_filename), "singleSource2_%s.png", parte_numerica);

    FILE *dot_file = fopen(dot_filename, "w");
    if (dot_file == NULL) {
        perror("Error al crear el archivo .dot");
        return 1;
    }

    // Encabezado 
    fprintf(dot_file, "graph SingleSource {\n");
    fprintf(dot_file, "  node [shape=circle, style=filled, fillcolor=lightblue];\n");
    fprintf(dot_file, "  edge [color=darkgreen];\n");
    
    for (int i = 0; i < numNodos; i++) {
        if (padre[i] != -1) { 
            int peso_arista = costo[i] - costo[padre[i]];
        
            fprintf(dot_file, "  %d -- %d [label=\"%d\"];\n", padre[i], i, peso_arista);
        }
    }
    fprintf(dot_file, "}\n"); // Cierre del grafo en DOT
    fclose(dot_file);

    // Mensajes de estado enviados a stderr para no interferir con la salida principal
    //fprintf(stderr, " -> Las aristas del árbol generador han sido guardadas en %s\n", dot_filename);
    //fprintf(stderr, " -> Generando imagen con Graphviz...\n");

    // Usamos snprintf para construir el comando del sistema de forma segura
    //snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_filename, png_filename);
    /*
    int result = system(command);

    if (result == 0) {
        fprintf(stderr, " -> ¡Grafo generado exitosamente en %s!\n", png_filename);
    } else {
        fprintf(stderr, " -> Error: Graphviz (comando 'dot') no se ejecutó correctamente.\n");
    }*/

    // SALIDA FINAL (stdout): Solo el tiempo, para que el script lo capture
    //printf("%.6f", tiempo_transcurrido);


    int suma_costos = 0;
    int nodos = 0;
    //int s = 0; //nodo inicial

    for(int i = 0; i < numNodos; i++){
        if(costo[i] < inf && i!=s){
            suma_costos += costo[i];
            nodos++;
        }
    }

    //printf("Costo del arbol: %d \n", suma_costos);






    return 0;
}