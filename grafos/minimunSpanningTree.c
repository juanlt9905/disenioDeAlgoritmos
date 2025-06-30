#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_ARISTAS 25000
#define MAX_NODOS 3000
#define arista_eliminada -2

typedef struct {
    int u;
    int v;
    int peso;
}Arista;
Arista aristas[MAX_ARISTAS]; //arreglo de estructuras tipo aristas
int padre[MAX_NODOS];

void swap(Arista* a, Arista* b) { //intercambio de aristas
    Arista temp=*a;
    *a=*b;
    *b=temp;
}


int partition(int p, int r) {
    int pivote = aristas[p].peso; 
    int i= p- 1;
    int j= r+1;

    while (1) {
        do {j--;} while (aristas[j].peso > pivote);//mover el
        do {i++;} while (aristas[i].peso < pivote);

        if (i<j) {
            swap(&aristas[i], &aristas[j]);
        }else{
            return j; 
        }
        
    }
}

void quickSort(int p, int r){
    int q;
    if (p<r){
        q=partition(p,r);
        quickSort(p,q);
        quickSort(q+1,r);
    }
}



void unirComponentes(int nodoA, int nodoB, int numNodos){

    int padreA = padre[nodoA];
    int padreB = padre[nodoB];
    for (int i=0; i<numNodos; i++){
        if(padre[i]==padreB){
            padre[i]=padreA;
        }
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

    //Ordenamiento de aristas de menor a mayor 
    quickSort(0, numAristas-1);

    struct timeval inicio, fin;
    double tiempo_transcurrido;
    gettimeofday(&inicio, NULL);
    //Inicializar componentes principales
    for (int i =0; i<numNodos; i++){
        padre[i]=i;
    }

    /*printf("Aristas: \n");
    for (int i =0; i<numAristas; i++){
        for (int j=0 ; j<2; j++)
            printf("%d ", aristas[i][j]);
        printf("\n");
    }*/

    int aristas_conteo = 0;
    Arista minimunST[numAristas];
    int longitud=0;
    for (int i=0; i<numAristas; i++){

        int u =aristas[i].u;
        int v =aristas[i].v;
        if (padre[u]!=padre[v]){
            //Agregar Arista
            //aristas[i][0]=arista_eliminada;
            //aristas[i][1]=arista_eliminada;
            minimunST[aristas_conteo]=aristas[i];
            longitud+=aristas[i].peso;
            aristas_conteo++;

            unirComponentes(u,v,numNodos);
        }    
    }
    gettimeofday(&fin, NULL);
    
    /*printf("******************Spanning Tree**********************\n"); 
    for (int i =0; i<numAristas; i++){
        for (int j=0 ; j<2; j++)
            printf("%d ", aristas[i][j]);
        printf("\n");
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

    snprintf(dot_filename, sizeof(dot_filename), "minimunST/minimunST_%s.dot", parte_numerica);
    snprintf(png_filename, sizeof(png_filename), "spanning3_%s.png", parte_numerica);

    FILE *dot_file = fopen(dot_filename, "w");
    if (dot_file == NULL) {
        perror("Error al crear el archivo .dot");
        return 1;
    }

    // Encabezado 
    fprintf(dot_file, "graph SpanningTree {\n");
    fprintf(dot_file, "  node [shape=circle, style=filled, fillcolor=lightblue];\n");
    fprintf(dot_file, "  edge [color=darkgreen];\n");
    
    // Escribir las aristas que forman parte del árbol generador
    for (int i = 0; i < aristas_conteo; i++){
        fprintf(dot_file, "  %d -- %d[label=\"%d\"];\n", minimunST[i].u, minimunST[i].v, minimunST[i].peso); 
    }
    fprintf(dot_file, "}\n"); // Cierre del grafo en DOT
    fclose(dot_file);

    // Mensajes de estado enviados a stderr para no interferir con la salida principal
    fprintf(stderr, " -> Las aristas del árbol generador han sido guardadas en %s\n", dot_filename);

    printf("Longitud del spanningTree: %d", longitud);
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
    

    
    
    

    return 0;
}
