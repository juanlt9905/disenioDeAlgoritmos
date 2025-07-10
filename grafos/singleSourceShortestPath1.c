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


TNodo * extraerColaConPrioridad(TNodo ** cola){
    if (*cola == NULL) {
        printf("Cola vacia\n");
        return NULL;
    }

    TNodo *temp = *cola; //puntero que recorrera la lista
    TNodo *min = *cola; //puntero que indicara donde esta el min
    TNodo *antesMinimo = NULL;
    TNodo *antes_temp = NULL;

    int min_prioridad = costo[(*cola)->info]; //extraemo

    while(temp != NULL){
        if (costo[temp->info]< min_prioridad){
            min_prioridad = costo[temp->info];
            min = temp;
            antesMinimo = antes_temp;
        }
        antes_temp =temp;
        temp = temp->sig;
    }
    TNodo * nodo_extraido = min;

    if(antesMinimo == NULL)
        //si antesMaximo es null, el maximo es el primer elemento.
        (*cola) = (*cola)->sig;
    else
        antesMinimo->sig = min->sig;
    
    return nodo_extraido;

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

void relaxation(int u, int v, int peso){
    if (costo[v]>costo[u]+peso){
        costo[v] =costo[u]+peso;
        padre[v] =u;
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

    TNodo *Q=NULL;
    for (int i=0; i<numNodos; i++){
        AgregarInicio(&Q, i);
    }
    //Inicializacion de  grafo fuente
    //verTodos(Q);
    
    int s=0;
    inicializar_fuente(s, numNodos);

    //toma de tiempo    
    struct timeval inicio, fin;
    double tiempo_transcurrido;
    gettimeofday(&inicio, NULL);

    while(Q!=NULL){
        TNodo * u = extraerColaConPrioridad(&Q);
        nodosProcesados[u->info]=1;
        TNodo *lista_sucesores = sucesores(u, numAristas);

        TNodo *sucesor_actual = lista_sucesores;
        while (sucesor_actual != NULL){
            //if (nodosProcesados[sucesor_actual->info]==0){
            relaxation(u->info, sucesor_actual->info, obtenerPeso(u->info, sucesor_actual->info, numAristas));
            sucesor_actual=sucesor_actual->sig; 
        }

    }

    gettimeofday(&fin, NULL);
    /*printf("Padres single-source1: \n");
    for (int i=0; i<numNodos; i++){
        printf("%d ", padre[i]);    
    }

    printf("\n Costos: \n");
    for(int i=0; i<numNodos; i++){
        printf("%d ", costo[i]);
    }*/

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
    snprintf(dot_filename, sizeof(dot_filename), "singleSourceScale/singleSource1_%s.dot", parte_numerica);
    snprintf(png_filename, sizeof(png_filename), "singleSource1_%s.png", parte_numerica);

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
    fprintf(stderr, " -> Las aristas del árbol generador han sido guardadas en %s\n", dot_filename);
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


    printf("Costo del arbol: %d \n", suma_costos);

    return 0;
}