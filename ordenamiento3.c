#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 



int main(){
    //Toma de tiempo de ejecución.
    struct timeval inicio, fin;
    long segundos, microsegundos;
    double tiempo_transcurrido;

    //Lectura de datos del archivo .txt
    int n, i;
    fscanf(stdin, "%d", &n);
    int arreglo[n];

    for(i=0; i<n; i++){// Llenado del arreglo a ordenar.
        fscanf(stdin, "%d", &arreglo[i]);
    }

    gettimeofday(&inicio, NULL); //Inicio de la toma temporal

    int pivote;
    for (int j=1; j<n;j++){
        pivote=arreglo[j]; //inicializamos el elemento a ordenar.
        int i=j-1; //inicializar indice adyacente del elemento que estamos comparando.
        while(i>=0 && arreglo[i]>pivote){//Para cada elemento anterior mayor a pivote,  
            arreglo[i+1] = arreglo[i];        //recorremos la lista a la derecha
            i=i-1;                
        }
        /*si salimos de la estructura while, significa que en a[i] se encuentra
         un elemento menor o igual al pivote, por lo que debemos colocar en
         a[i+1] a pivote*/
        arreglo[i+1]=pivote;


    }
    gettimeofday(&fin, NULL);

    segundos = fin.tv_sec - inicio.tv_sec;
    microsegundos = fin.tv_usec - inicio.tv_usec;
    tiempo_transcurrido = segundos + microsegundos*1e-6;

    printf("%.8f", tiempo_transcurrido);

    //for(int i=0; i<n; i++){
    //    printf("%d\n", arreglo[i]);
    //}
    // Abre un archivo en modo escritura
    FILE *file2 = fopen("lista3_numeros_ordenados.txt", "w");
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