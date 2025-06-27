#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#define MAX 25000
#define MAX_NODOS 3000 
int aristas[MAX][2];
int nodos_visitados[MAX_NODOS];


typedef struct nodo{
    int info;
    struct nodo * sig; //apuntador al siguiente nodo en la lista enlazada
    struct nodo * padre;
}TNodo;

void AgregarInicio(TNodo**lista, int dato, TNodo *padre){//Agrega un nodo al inicio de una lista.
    //puntero doble, ya que modificamos la cabecera de la lista
    TNodo *nuevo=NULL;
    //Agregar memoria para el nuevo nodo
    nuevo=(TNodo*) malloc(sizeof(TNodo));

    nuevo->info=dato; //Asigna el valor a nodo
    nuevo->padre=padre;
    nuevo->sig= *lista; //Coloca nodo al inicio de lista
    *lista = nuevo; //El inicio de lista cambia al nuevo

}
void VerTodos(TNodo*lista){ //Muestra todos los nodos de la lista

    while(lista!=NULL){
        printf("%d ", lista->info);

        lista=lista->sig;

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
int estadoEnCamino(TNodo *nodo_actual, int dato){// busca los estados en una ramificacion mediante el padre
    // si el nodo actual no tiene padre, no hay backtracking
    if (nodo_actual->padre == NULL) {
        return 0;
    }

    //comprobar si el dato que buscamos es el padre inmediato, si lo es, es un ciclo falso
    if (nodo_actual->padre->info == dato) {
        return 0;
    }
    //empezamos la busqueda desde el padre.
    TNodo *temp = nodo_actual->padre;
    while(temp != NULL){
        if(temp->info==dato){
            return 1; // se encontro estado
        }
        temp = temp->padre;
    }
    return 0;//no se encontro estado
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

int busquedaPorProfundidad(TNodo *nodo_inicial, int numAristas){ //
    printf("--- Busqueda inicianda para nodo: %d ---\n", nodo_inicial->info); 
    TNodo *abiertos=NULL;
    int ciclo_encontrado=0;

    //VERIFICACION DE SI EL NODO YA FUE VISITADO
    if (nodos_visitados[nodo_inicial->info]==1) return 0;  
    
    //hacer abiertos la pila formada por el nodo inicial
    AgregarInicio(&abiertos, nodo_inicial->info, nodo_inicial->padre);
    
    //Mientras abiertos no este vacio
    while(abiertos!=NULL){
        //Hacer estado actual el primer nodo de abiertos.
        TNodo *nodo_actual= abiertos;
        printf("--- Nodo actual: %d ---\n", nodo_actual->info); 
        abiertos=abiertos->sig; //hacer abiertos el resto de abiertos

        nodos_visitados[nodo_actual->info] =1; //Marcar como visitado

        TNodo * nuevos_sucesores = sucesores(nodo_actual, numAristas);
        TNodo *temp= nuevos_sucesores;
        printf("---Hijos:--- \n");
        VerTodos(nuevos_sucesores);
        printf("\n");
        //AGREGAR NUEVOS SUCESORES AL INICIO DE ABIERTOS (BUSQUEDA POR PRFUNDIDAD)
        while (temp!=NULL){ 
            
            if(estadoEnCamino(nodo_actual, temp->info)==0){
                    if(nodos_visitados[temp->info]==0 )AgregarInicio(&abiertos, temp->info, nodo_actual);// Pila
            }
            else{ //omitimos ciclos inmediatos por ser aristas no dirigidas
                ciclo_encontrado=1; //se encontro un ciclo
                break;
            }
            temp=temp->sig;
        }
        liberarLista(nuevos_sucesores);
        //free(nodo_actual);
        
        if (ciclo_encontrado==1) break;

    }
    liberarLista(abiertos);
    return ciclo_encontrado;
}

int main(){


    FILE *file = fopen("grafo_grande.txt", "r");
    int numAristas, numNodos;
    fscanf(file, "%d", &numNodos); // nodos de 0 a numNodos-1.
    fscanf(file, "%d", &numAristas);

    //almacenar las aristas en la matriz aristas[][]
    for(int i=0; i<numAristas; i++){
        for(int j=0; j<2; j++)
            fscanf(file, "%d", &aristas[i][j]);
    }

    fclose(file); 
    //inicializacion de nodos visitados.
    for (int i=0; i<numNodos; i++) 
        nodos_visitados[i] = 0;

    //haremos la busqueda por anchura iterando el nodo raiz sobre cada nodo
    TNodo *raiz=NULL;
    raiz=(TNodo*)malloc(sizeof(TNodo)); //inicializar un nodo
    raiz->sig =NULL;
    raiz->padre=NULL;

    int ciclo_grafo=0;
    //Iteracion sobre los nodos para la busqueda por profundidad.
    for (int i=0; i<numNodos; i++){
        if(nodos_visitados[i]==0){
            raiz->info = i;
            //iniciamos busqueda por el nodo inexplorado
            if(busquedaPorProfundidad(raiz, numAristas)==1){
                ciclo_grafo =1;
                break;
            }
        }
    }

    free(raiz);

    if (ciclo_grafo ==1)
        printf("Se encontro un cilco en el grafo. \n");
    else
        printf("NO se encontro ciclo en el grafo. \n");

    return 0;
}