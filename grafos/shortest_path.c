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
    
    int s=0;
    inicializar_fuente(s, numNodos);

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










    return 0;
}