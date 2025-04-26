#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/time.h> 

int main(int argc, char **argv){

    int posicion;
    //Lectura de datos del archivo .txt
    int i, aux;
    int n = atoi(argv[1]);
    int arreglo[n];

    for(i=0; i<n; i++){

        fscanf(stdin, "%d", &arreglo[i]);

    }
    //int desorden[] = {8,90,5,4,7,3,6,10};
    //int desorden[] = {8,6,7,5,4,3,2,1};
    int indice[n];
    memset(indice, 0, sizeof(indice)); //llenar de 0 todo el arreglo.
    int orden[n];   
    //Toma de tiempo
    struct timeval inicio, fin;
    long segundos, microsegundos;
    double tiempo_transcurrido;


    gettimeofday(&inicio, NULL);
    //Comienzo del ordenamiento
    int min;
    for (int j=0; j<n ; j++){    //** C1   Se ejecuta n+1 veces */

        //Encontrar el primer elemento con la bandera 0 para inicializar el minimo min.
        for (int i = 0; i < n; i++) { //**C2 se ejecuta n(n+1) veces en el peor de los casos */
            if (indice[i] == 0) {     //**C3 se ejecuta n(n) veces */
                min = arreglo[i];     //**C4 se ejecuta n(n) veces en el peor de los casos */ 
                posicion = i;           //**C5 se ejecuta n(n) veces */
                break;                      
            }
        }

        //buscar el minimo de la lista desordenada
        for (int i=0 ; i<n; i++){  //** C6 se ejecuta n(n+1) */

            if (indice[i] == 0 && min>arreglo[i]){  //**C7 se ejecuta n(n) */
                min = arreglo[i];      //**C8 se ejecuta n(n) */
                posicion = i;           //**C9 se ejecuta n(n) */
            } 
        }

        //Colocar el minimo de la lista desordenada en el siguiente elemento de la lista ordenada,
        // y marcar la bandera del elemento ya ordenado.
        orden[j] = min;  //**C10 se ejecuta n veces */
        indice[posicion] = 1; //**C11 se ejecuta n veces */

    }

    gettimeofday(&fin, NULL);

    segundos = fin.tv_sec - inicio.tv_sec;
    microsegundos = fin.tv_usec - inicio.tv_usec;
    tiempo_transcurrido = segundos + microsegundos*1e-6;

    printf("%.8f", tiempo_transcurrido);

    //imprimir la lista ya ordenada
    /*for(int i = 0; i<n ; i++){
        printf("%d\n", orden[i]);
    }*/

    FILE *file2 = fopen("lista1_numeros_ordenados.txt", "w");
    if (file2 == NULL) {
        printf("Error al abrir el archivo!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {         
        // Escribe el número en el archivo seguido de un salto de línea
        fprintf(file2, "%d\n", orden[i]);
    }

    // Cierra el archivo
    fclose(file2);
    
    return 0;

}