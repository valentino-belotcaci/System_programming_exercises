#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int check_length(char * line){
    int len = 0;
    char * p = line;

    while(*p != '\n'){
        if(*p == EOF)
            return -1;
        len++;
        p++;
    }
    return len++;
}

int main(int argc, char * argv[]){

    int min = 0;
    int max = INT_MAX;

    if (argc > 1)
        min = atoi(argv[1]);

    if (argc > 2)
        max = atoi(argv[2]);

    int c = 0;
    int length = 0;

    char line[5001];

    while(fgets(line, 5001, stdin)){

        int len = check_length(line);
        //printf("len = %d\n", len);
        int flag = 0;

        if (len >= min && len <= max){
            for(int i = 0; i < len; i++){

                if (i < 60)
                    printf("%c", line[i]);
                else {
                    flag = 1;
                    printf("...");
                    break;
                }
            }
            printf("\n");
        }
    }

}