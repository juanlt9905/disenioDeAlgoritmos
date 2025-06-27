#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_ARISTAS 25000
#define MAX_NODOS 3000
#define arista_eliminada -2

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
        if (aristas[i][0]!=-2){
            if (aristas[i][0]== valor_nodo) AgregarInicio(&sucesores, aristas[i][1], nodo_actual);
            else if (aristas[i][1]== valor_nodo) AgregarInicio(&sucesores, aristas[i][0], nodo_actual);
        }
    }


    return sucesores;
}

void eliminarArista(int nodo1, int nodo2, int numAristas){
    for(int i=0; i<numAristas; i++){
        if ((aristas[i][0]==nodo1 && aristas[i][1]==nodo2) || (aristas[i][0]==nodo2 && aristas[i][1]==nodo1)){
            aristas[i][0]= arista_eliminada;
            aristas[i][1]= arista_eliminada;
            return;    
        }
    }
}
int busquedaCicloRecursiva(TNodo *nodo_actual, int numAristas, int padre_info) {

    nodos_visitados[nodo_actual->info]=1;

    //Obtenemos los sucesores del nodo actual e iteramos
    TNodo *lista_sucesores = sucesores(nodo_actual, numAristas);
    TNodo *sucesor_actual = lista_sucesores;
    while (sucesor_actual != NULL){
        if(sucesor_actual->info != padre_info){
            if (nodos_visitados[sucesor_actual->info]==1){ 
                eliminarArista(sucesor_actual->info, nodo_actual->info, numAristas);
                liberarLista(lista_sucesores);  // Liberar antes de retornar
                return 1;                
            }
            if(busquedaCicloRecursiva(sucesor_actual, numAristas, nodo_actual->info)==1){
                liberarLista(lista_sucesores); 
                return 1;}
            }   
            //Avanzo al siguiente sucesor
        sucesor_actual=sucesor_actual->sig;
    }
    liberarLista(lista_sucesores);
    return 0; //aqui ya se exploro todos los sucesores de nodo_actual, si se llego a este punto,
                // nodo_actual no llega a ningun ciclo. Por lo tanto, 
}



int main(int argc, char *argv[]){

    //Variables para la toma de tiempo
    struct timeval inicio, fin;
    long segundos, microsegundos;
    double tiempo_transcurrido;


    const char *inputfile= argv[1];
    FILE *file = fopen(inputfile, "r");
    int numAristas, numNodos;
    fscanf(file, "%d", &numNodos); // nodos de 0 a numNodos-1.
    fscanf(file, "%d", &numAristas);

    //almacenar las aristas en la matriz aristas[][]
    for(int i=0; i<numAristas; i++){
        for(int j=0; j<2; j++)
            fscanf(file, "%d", &aristas[i][j]);
    }
    
    fclose(file); 

    int aristas_eliminadas_count = 0;
    /*for (int i =0; i<numAristas; i++){
        for (int j=0 ; j<2; j++)
            printf("%d ", aristas[i][j]);
        printf("\n");}*/

    //Definir el nodo inicial de la busqueda
    TNodo *nodo_inicial = (TNodo*) malloc(sizeof(TNodo));
    nodo_inicial->info = 0;
    nodo_inicial->padre = NULL;
    nodo_inicial->sig = NULL;
    //TOMA DE TIEMPO
    gettimeofday(&inicio, NULL);
    int m=numAristas;
    int ciclo;
    while(m>numNodos-1){
        for (int i =0; i<numNodos; i++){
            nodos_visitados[i] = 0;
        }

        ciclo=busquedaCicloRecursiva(nodo_inicial, numAristas, -1);
        
        m=m-1;
        aristas_eliminadas_count++;
        fprintf(stderr, "Progreso: %d aristas de ciclo eliminadas.\r", aristas_eliminadas_count);
        fflush(stderr); // Forzar que el mensaje aparezca inmediatamente 
    }

    //FIN DE TOMA DE TIEMPO
    gettimeofday(&fin, NULL);

    segundos = fin.tv_sec - inicio.tv_sec;
    microsegundos = fin.tv_usec - inicio.tv_usec;
    tiempo_transcurrido = segundos + microsegundos*1e-6;

    //printf("%.8f", tiempo_transcurrido);

    /*
    printf("******************Spanning Tree**********************\n"); 
    for (int i =0; i<numAristas; i++){
        for (int j=0 ; j<2; j++)
            printf("%d ", aristas[i][j]);
        printf("\n");}
    */
    /*Visualizacion de GRAFO*/

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
    snprintf(dot_filename, sizeof(dot_filename), "scaleup1/spanning1_%s.dot", parte_numerica);
    snprintf(png_filename, sizeof(png_filename), "spanning1_%s.png", parte_numerica);

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
    for (int i = 0; i < numAristas; i++){
        if (aristas[i][0] != arista_eliminada){ 
            fprintf(dot_file, "  %d -- %d;\n", aristas[i][0], aristas[i][1]); 
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
    printf("%.6f", tiempo_transcurrido);

    return 0;
}