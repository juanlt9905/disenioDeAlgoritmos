#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>

void naive1(char *T, char *P) {
    int n = strlen(T);
    int m = strlen(P);
    
    //iteramos sobre todos los posibles shifts
    for (int s = 0; s <= n - m; s++) {
        int j;
        //verificamos si el desplazamiento actual coincide con  el patron
        for (j = 0; j < m; j++) {
            if (T[s + j] != P[j]) {
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


    char *texto =argv[1];
    char *patron =argv[2];

    printf("Texto:  %s\n", texto);
    printf("Patron: %s\n\n", patron);

    naive1(texto, patron);

    return 0; 




    return 0; 
}