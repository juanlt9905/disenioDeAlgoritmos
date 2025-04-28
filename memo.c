#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) { return a > b ? a : b; }

int lcss_memo(char *a, char *b, int i, int j, int **memo) {
    if (a[i] == '\0' || b[j] == '\0') return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (a[i] == b[j])
        memo[i][j] = 1 + lcss_memo(a, b, i+1, j+1, memo);
    else
        memo[i][j] = max(lcss_memo(a, b, i+1, j, memo), lcss_memo(a, b, i, j+1, memo));
    return memo[i][j];
}

int main(int argc, char **argv) {
    if (argc<3) return 1;
    char *a = argv[1];
    char *b = argv[2];
    int lenA = strlen(a), lenB = strlen(b);
    int **memo = malloc(lenA * sizeof(int*));
    for(int i=0; i<lenA; i++) {
        memo[i] = malloc(lenB * sizeof(int));
        for(int j=0; j<lenB; j++) memo[i][j] = -1;
    }

    int result = lcss_memo(a, b, 0, 0, memo);
    printf("La longitud maxima de la cadena comun es: %d\n", result);

    // limpieza
    for(int i=0;i<lenA;i++) free(memo[i]);
    free(memo);
    return 0;
}