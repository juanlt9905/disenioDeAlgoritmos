#include <stdio.h>
#define MAXIMO 1000000
#include <sys/time.h> 


int main(){

    struct timeval inicio, fin;
    long segundos, microsegundos;
    double tiempo_transcurrido;

    //Lectura de datos del archivo .txt
    int n, i, aux;
    fscanf(stdin, "%d", &n);
    int arreglo[n];

    for(i=0; i<n; i++){

        fscanf(stdin, "%d", &arreglo[i]);

    }

    gettimeofday(&inicio, NULL);

    //Algoritmo de Ordenacion 
    
    for (i=0; i<n; i++){

        //min = arreglo[i];
        int posicion_minimo = i;
        for(int j=i+1; j<n; j++){  //encontrar la posicion del elemento menor
            if (arreglo[posicion_minimo] > arreglo[j]){
                posicion_minimo = j;
            }

        }
        if (posicion_minimo !=i){ //swap(a,b) colocar el elemento de menor valor en la posicion correspondiente.
            aux = arreglo[i];
            arreglo[i] = arreglo[posicion_minimo];
            arreglo[posicion_minimo] = aux;
        }
        
    }

    gettimeofday(&fin, NULL);

    segundos = fin.tv_sec - inicio.tv_sec;
    microsegundos = fin.tv_usec - inicio.tv_usec;
    tiempo_transcurrido = segundos + microsegundos*1e-6;

    printf("%.8f",tiempo_transcurrido);
    /*for (i=0; i<n; i++){

        printf("%d\n", arreglo[i]);
    }*/
    FILE *file2 = fopen("lista2_numeros_ordenados.txt", "w");
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