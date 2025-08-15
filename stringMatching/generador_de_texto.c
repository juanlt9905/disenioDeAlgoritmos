#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    
    long tamano = 50;
    char *patron = "juan";
    int longitud_patron = strlen(patron);
    
    FILE *archivo = fopen("texto_grande.txt", "w");
    if (archivo == NULL) {
        perror("Error al crear el archivo");
        return 1;
    }

    srand(time(NULL)); // Inicializar la semilla para números aleatorios

    for (long i = 0; i < tamano; i++) {
        // Inserta el patrón cada 1000 caracteres para tener coincidencias
        if (i % 10 == 0) {
            fprintf(archivo, "%s", patron);
            i += longitud_patron - 1; // Ajusta el índice
        } else {
            // Genera un carácter aleatorio (letras minúsculas)
            char caracter_aleatorio = 'a' + (rand() % 26);
            fputc(caracter_aleatorio, archivo);
        }
    }

    fclose(archivo);
    printf("Archivo 'texto_grande.txt' de %ld bytes generado con éxito.\n", tamano);

    return 0;
}