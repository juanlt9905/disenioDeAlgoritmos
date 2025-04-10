#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

/*
char * crearSubarreglo(char * arreglo, int inicio, int fin){

    int n = fin - inicio+1; //taman;io del subarreglo
    char *subarreglo = (char *)malloc((n+1) * sizeof(char)); // Asignar memoria para el subarreglo

    for (int i = 0; i < n; i++) {
        subarreglo[i] = arreglo[inicio + i];
    }

    subarreglo[n] = '\0';

    return subarreglo;
}
*/

int lcss(char * a, char *b){
    int i=0;
    int na=0;
    int nb=0;
    
    if (*a=='\0'|| *b=='\0'){
        return 0;
    }
    else if (a[0]==b[0]){
        return 1 + lcss(a+1, b+1);
    }
    else{
        int l_a_subb = lcss(a, b+1);
        int l_suba_b = lcss(a+1, b);
        if (l_a_subb>=l_suba_b)
            return l_a_subb;
        else
            return l_suba_b;
    }
}


int main(int argc, char **argv){

    //char a[] = "AAA";
    //char b[] = "ACBAD";
    char *a = argv[1];
    char *b = argv[2];
    
    int x = lcss(a,b);

    printf("La longitud maxima de la cadena comun es: %d\n", x);

    return 0;
}