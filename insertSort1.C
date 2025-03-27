#include <stdio.h>
//Ordenamiento no descendiente. Introduccion a Algoritmos Cormen.
int main(){

    int lista[] = {9,8,7,6,5,4,3,2,1};
    
    int tam_lista = sizeof(lista)/sizeof(lista[0]);
    printf("Lista DESORDENADA: \n");
    for (int i = 0; i<tam_lista;i++) printf("%d ", lista[i]);
   
    for (int j=1; j< tam_lista ;j++){
        int key = lista[j];
        int i = j-1;
        while(i>-1 && lista[i]>key){
            lista[i+1] = lista[i];
            i = i-1;
        }
        lista[i+1] = key;
        

        //printf("%d\n",lista[i]);
    }

    printf("Lista ORDENADA: \n");
    for (int i = 0; i<tam_lista;i++) printf("%d ", lista[i]);
    return 0;
}