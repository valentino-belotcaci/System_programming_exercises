#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]){

    int n = 0;

    if (argc > 1)
        n = atoi(argv[1]);

    for(int i = 1; i <= n; i++){
        for(int j = n - i; j > 0; j--){
            putchar(' ');
        }
        for(int k = 1; k < 2 * i; k++){
            putchar('#');
        }
        putchar('\n');
    }

    for(int i = n - 1; i > 0; i--){
        for(int j = n - i; j > 0; j--){
            putchar(' ');
        }
        for(int k = 1; k < 2 * i; k++){
            putchar('#');
        }
        putchar('\n');
    }
}