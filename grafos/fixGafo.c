#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARISTAS 25000
#define MAX_NODOS 3000
#define arista_eliminada -2

/*Tomamos un bosque y lo transformamos en un grafo conectado*/
int aristas[MAX_ARISTAS][2];

typedef struct nodo {
    int info;
    struct nodo *sig;
    struct nodo *nodoPadre;
} TNodo;

int padre[MAX_NODOS];

void eliminarArista(int nodo1, int nodo2, int numAristas){
    for(int i=0; i<numAristas; i++){
        if ((aristas[i][0]==nodo1 && aristas[i][1]==nodo2) || (aristas[i][0]==nodo2 && aristas[i][1]==nodo1)){
            aristas[i][0]= -2;
            aristas[i][1]= -2;    
        }
    }
}

void unirComponentes(int nodoA, int nodoB, int numNodos){

    for (int i=0; i<numNodos; i++){
        if(padre[i]==padre[nodoB]){
            padre[i]=padre[nodoA];
        }
    }
}
int main(){

    char inputfile[]= "grafo_grande.txt";
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
    //Inicializar componentes principales
    for (int i =0; i<numNodos; i++){
        padre[i]=i;
    }


    for (int i=0; i<numAristas; i++){
        unirComponentes(aristas[i][0], aristas[i][1], numNodos);
    }

    //Padre almacenara los componentes.
    //for (int i=0; i<numNodos; i++){
    //    printf("%d ", padre[i]);
    //}

    //ALMACENAR LOS VALORES UNICOS DE PADRES, para unirlos
    int componentes_padres[MAX_NODOS]; 
    int num_componentes = 0;
    
    // rreglo para marcar los componentes ya guardados
    int componente_visitado[MAX_NODOS] = {0}; 

    for (int i = 0; i < numNodos; i++){

        int padre_actual = padre[i];
        
        //Si no se ha guardado al padre de este componente, lo guardamos en componentes_padres
        if (componente_visitado[padre_actual]==0) {
            
            componente_visitado[padre_actual]=1;
            
            // Almacenamos al padre en el arreglo de componentes
            componentes_padres[num_componentes] = i;
            num_componentes++;
        }
    }


    int aristas_nuevas[MAX_ARISTAS][2];
    int num_aristas_nuevas=0;
    //Unir componentes
    if(num_componentes>1){
        for (int i=0; i<num_componentes-1; i++){

            aristas_nuevas[num_aristas_nuevas][0]=componentes_padres[i];
            aristas_nuevas[num_aristas_nuevas][1]=componentes_padres[i+1];

            num_aristas_nuevas++;
        }
    }   
    printf("DIAGNOSTICO: Se van a agregar %d aristas nuevas.\n", num_aristas_nuevas); 

    //escribir las aristas nuevas en .txt destino
    printf("\nActualizando el archivo 'grafo.txt'\n");
    FILE *outfile = fopen(inputfile, "w"); 
    if (outfile == NULL) {
        perror("Error al abrir grafo.txt para escribir");
        return 1;
    }

    int total_aristas = numAristas + num_aristas_nuevas;
    fprintf(outfile, "%d\n", numNodos);
    fprintf(outfile, "%d\n", total_aristas);

    for (int i = 0; i < numAristas; i++) {
        fprintf(outfile, "%d %d\n", aristas[i][0], aristas[i][1]);
    }
    for (int i = 0; i < num_aristas_nuevas; i++) {
        fprintf(outfile, "%d %d\n", aristas_nuevas[i][0], aristas_nuevas[i][1]);
    }
    fclose(outfile);
    printf("Archivo actualizado \n");
    
    
    

    return 0;
}
