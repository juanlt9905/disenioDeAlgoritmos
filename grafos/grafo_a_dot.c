#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARISTAS 25000
#define MAX_NODOS 3000
#define arista_eliminada -2

int aristas[MAX_ARISTAS][2];
int nodos_visitados[MAX_NODOS];



int main(int argc, char *argv[]){


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



        /*Visualizacion de GRAFO*/
    FILE *dot_file = fopen("grafo_prueba_conectado.dot", "w");
    if (dot_file == NULL) {
        perror("Error al crear el archivo spanning_tree.dot");
        return 1;
    }

    // Encabezado 
    fprintf(dot_file, "graph SpanningTree1 {\n");
    // Estilos
    fprintf(dot_file, "  node [shape=circle, style=filled, fillcolor=lightblue];\n");
    fprintf(dot_file, "  edge [color=darkgreen];\n");
    
    // Escribir las aristas que forman parte del árbol generador
    for (int i = 0; i < numAristas; i++){
        if (aristas[i][0] != arista_eliminada) { 
            fprintf(dot_file, "  %d -- %d;\n", aristas[i][0], aristas[i][1]); 
        }
    }
    fprintf(dot_file, "}\n"); // Cierre del grafo en DOT
    fclose(dot_file);

    printf("Las aristas del árbol generador han sido guardadas en spanning_tree1.dot\n");
   // printf("Generando imagen con Graphviz...\n");

    // Ejecutar Graphviz para generar la imagen PNG
    // Asegúrate de que 'dot' esté en tu PATH del sistema
    /*int result = system("dot -Tpng grafo_prueba_conectado.dot -o grafo_prueba_conectado.png");

    if (result == 0) {
        printf("¡Grafo generado exitosamente en spanning_tree1.png!\n");
    } else {
        fprintf(stderr, "Error: Graphviz (comando 'dot') no se ejecutó correctamente.\n");
        fprintf(stderr, "Asegúrate de tener Graphviz instalado y 'dot' en tu PATH.\n");
        return 1;
    }*/





    return 0;
}