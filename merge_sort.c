#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

void mezclarListasOrdenadas(int *arreglo, int inicio, int medio, int fin){ 
    /*Recibe un arreglo cuya primera mitad
    esta ordenada, asi como su segunda mitad. Tambien recibe
    su longitud*/
    int n = fin- inicio +1;
    int aux[n]; // arreglo auxiliar donde sera ordenada la lista


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


     //Lectura de datos del archivo .txt
    int n, i;
    fscanf(stdin, "%d", &n);
    int arreglo[n];
 
    for(i=0; i<n; i++){
 
        fscanf(stdin, "%d", &arreglo[i]);
 
    }
    
    struct timeval inicio2, fin2;
    long segundos, microsegundos;
    double tiempo_transcurrido;

    gettimeofday(&inicio2, NULL);
 
    merge_sort(arreglo, 0, n - 1);

    gettimeofday(&fin2, NULL);

    segundos = fin2.tv_sec - inicio2.tv_sec;
    microsegundos = fin2.tv_usec - inicio2.tv_usec;
    tiempo_transcurrido = segundos + microsegundos*1e-6;

    printf("%.8f",tiempo_transcurrido);

    //for (int i=0; i<n; i++){
    //    printf("%d ", arreglo[i]);
    //}
    FILE *file2 = fopen("lista_merge_numeros_ordenados.txt", "w");
    if (file2 == NULL) {
        printf("Error al abrir el archivo!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {         
        // Escribe el número en el archivo seguido de un salto de línea
        fprintf(file2, "%d\n", arreglo[i]);
    }

    // Cierra el archivo
    fclose(file2);


    



    return 0;  
}