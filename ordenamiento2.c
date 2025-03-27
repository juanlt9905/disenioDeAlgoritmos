#include <stdio.h>
#define MAXIMO 100
#include <sys/time.h> 
int arreglo[MAXIMO];


int main(){

    struct timeval inicio, fin;
    long segundos, microsegundos;
    double tiempo_transcurrido;

    //Lectura de datos del archivo .txt
    int n, i, aux;
    fscanf(stdin, "%d", &n);

    for(i=0; i<n; i++){

        fscanf(stdin, "%d", &arreglo[i]);

    }

    gettimeofday(&inicio, NULL);

    //Algoritmo de Ordenacion 
    
    for (i=0; i<n; i++){

        //min = arreglo[i];
        int posicion_minimo = i;
        for(int j=i+1; j<n; j++){
            if (arreglo[posicion_minimo] > arreglo[j]){
                posicion_minimo = j;
            }

        }
        if (posicion_minimo !=i){
            aux = arreglo[i];
            arreglo[i] = arreglo[posicion_minimo];
            arreglo[posicion_minimo] = aux;
        }
        
    }

    gettimeofday(&fin, NULL);

    segundos = fin.tv_sec - inicio.tv_sec;
    microsegundos = fin.tv_usec - inicio.tv_usec;
    tiempo_transcurrido = segundos + microsegundos*1e-6;

    printf("Tiempo transcurrido: %.6f segundos\n", tiempo_transcurrido);
    for (i=0; i<n; i++){

        printf("%d\n", arreglo[i]);
    }

    return 0;
}