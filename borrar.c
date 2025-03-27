#include <stdio.h>
#include <string.h> 

int main(){

    int n=3;
    int vec[n];

    memset(vec, 0, sizeof(vec)); 

    for (int i=0; i<n; i++){

        printf("%d", vec[i]);

    }



    return 0;
}