#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

void mezclarListasOrdenadas(int *arreglo, int inicio, int medio, int fin){ 
    /*Recibe un arreglo cuya primera mitad
    esta ordenada, asi como su segunda mitad. Tambien recibe
    su longitud*/
    int n = fin- inicio +1;
    int aux[n]; // arreglo auxiliar donde sera ordenada la lista
    //int medio = n/2 -1;

    int k=0;
    int i=inicio;
    int j= medio+1;

    while(i<=medio && j<=fin){
        if (arreglo[i]<arreglo[j]){
            aux[k] = arreglo[i];
            i++;
        }
        else if (arreglo[j]<arreglo[i]){
            aux[k] = arreglo[j];
            j++;
        }
        k++;
    }

    while(i <= medio){
        aux[k] = arreglo[i];
        i++;
        k++;
    }

    while (j<=fin){
        aux[k] = arreglo[j];
        j++;
        k++; 
    }
    for (int i = 0; i < n; i++) {
        arreglo[inicio +i] = aux[i];    
    }
}

void merge_sort(int *arreglo, int inicio, int fin){
    if (inicio < fin) { // si el arreglo tiene longitud mayor a 1
        int medio = inicio + (fin - inicio) / 2;// punto medio del arreglo
    
        // Ordenar la primera y segunda mitad
        merge_sort(arreglo, inicio, medio);// ordena la primera parte
        merge_sort(arreglo, medio + 1, fin);//ordena la segunda parte
    
        // combina las partes ordenadas
        mezclarListasOrdenadas(arreglo, inicio, medio, fin);
    }
    //si el arreglo es de longitud 1, ya esta ordenado (caso base)
}
int main(){

    int arreglo[] = {111, 30, 5, 12,-14, 6, 84, 190,11};
    int n = sizeof(arreglo)/sizeof(arreglo[0]);

    merge_sort(arreglo, 0, n - 1);

    for (int i=0; i<n; i++)
        printf("%d ", arreglo[i]);
    



    return 0;  
}