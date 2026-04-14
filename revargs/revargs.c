#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
revargs: Write a C program called revargs that takes a number of command-line arguments A1, A2, ..., 
and prints on the standard output every pair of arguments Ai Aj, 
with i<j, such that Ai is the reverse string of Aj (and vice-versa).
*/

char* reverse(const char* s) {
    int len = strlen(s);
    char* res = malloc(len + 1); // +1 for '\0'

    if (!res) return NULL;

    for (int i = 0; i < len; i++) {
        res[i] = s[len - 1 - i];
    }

    res[len] = '\0';
    return res;
}


int main(int argc, char * argv[]){
    
    char *res;

    for (int i = 1; i < argc - 1; i++){

        res = reverse(argv[i]);

        for (int j = i + 1; j < argc; j++){

            if(strcmp(res, argv[j]) == 0){
                printf("%s ", argv[i]);
                printf("%s", argv[j]);
                printf("\n");
            }
        }
        free(res);
    }
}
