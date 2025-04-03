#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main() {
    // Inicializa el generador de números aleatorios
    srand(time(NULL));

    int n=100000; //
    // Abre un archivo en modo escritura
    FILE *file = fopen("lista_numeros_aleatorios.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo!\n");
        return 1;
    }

    fprintf(file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        // Genera un número aleatorio
        int numero = rand() % 1000; 
        // Escribe el número en el archivo seguido de un salto de línea
        fprintf(file, "%d\n", numero);
    }

    // Cierra el archivo
    fclose(file);

    return 0;
}