#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>

int hashSuma(char * a, int longitud){
    int suma=0;

    for (int i=0; i<longitud; i++){
        suma+=a[i];
    }

    return suma;
}
int main(int argc, char *argv[]){
    //char a[]="ab";
    //printf("a+b: %d\n", hashSuma(a));

    
    //char *t =argv[1];
    char *p =argv[2];

    //Lectura del archivo de texto.
    FILE *archivo;
    char *t;
    long tamano_archivo;

    archivo = fopen(argv[1], "r");

    // Obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END); //coloca el puntero al final del archivo.
    tamano_archivo = ftell(archivo);//devuelve la posicion del puntero en el archivo.
    fseek(archivo, 0, SEEK_SET);//devuelve el puntero al inicio para su posterior lectura.

    //Asignar memoria para el texto (+1 para el carácter nulo '\0')
    t = (char *)malloc(tamano_archivo + 1);

    //Leer todo el contenido del archivo en la memoria
    fread(t, 1, tamano_archivo, archivo);
    t[tamano_archivo] = '\0'; // Asegurar que es una cadena terminada en nulo

    // Cerrar el archivo
    fclose(archivo);

    int n = strlen(t);
    int m = strlen(p);

    int hashPatron= hashSuma(p, m);
    
    //iteramos sobre todos los posibles shifts
    for (int s=0; s <=n-m; s++) {
        
        if (hashSuma(&t[s], m)== hashPatron){ //comparacion entre hash de ventana actual y patron
        
            int j;
            //verificamos si la ventana actual coincide con  el patron
            for (j=0; j<m; j++) {
      
                if (t[s+j]!=p[j]) {
                    break; // si los caracteres no coinciden se rompe el bucle
                }
            }

            //si j==m, se completo un patron dentro del texto
            if (j == m) {
                printf("Patron encontrado en el indice %d\n", s);
            }
        }
    }
    
    
    return 0;
}