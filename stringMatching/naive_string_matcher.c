#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>



void naive1(char *t, char *p) {
    int n = strlen(t);
    int m = strlen(p);
    
    //iteramos sobre todos los posibles shifts
    for (int s=0; s <=n-m; s++) {
        int j;
        //verificamos si la ventana actual coincide con  el patron
        for (j=0; j<m; j++) {
            if (t[s + j] != p[j]) {
                break; // si los caracteres no coinciden se rompe el bucle
            }
        }

        //si j==m, se completo un patron dentro del texto
        if (j == m) {
            printf("Patron encontrado en el indice %d\n", s);
        }
    }
}




int main(int argc, char *argv[]){


    //char *texto =argv[1];
    char *patron =argv[2];

        // --- Lógica para leer el archivo de texto ---
    FILE *archivo;
    char *texto;
    long tamano_archivo;

    archivo = fopen(argv[1], "r");

    // Obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END); //coloca el puntero al final del archivo.
    tamano_archivo = ftell(archivo);//devuelve la posicion del puntero en el archivo.
    fseek(archivo, 0, SEEK_SET);//devuelve el puntero al inicio para su posterior lectura.

    //Asignar memoria para el texto (+1 para el carácter nulo '\0')
    texto = (char *)malloc(tamano_archivo + 1);

    //Leer todo el contenido del archivo en la memoria
    fread(texto, 1, tamano_archivo, archivo);
    texto[tamano_archivo] = '\0'; // Asegurar que es una cadena terminada en nulo

    // Cerrar el archivo
    fclose(archivo);

    printf("Texto:  %s\n", texto);
    printf("Patron: %s\n", patron);

    naive1(texto, patron);

    return 0; 




    return 0; 
}