#include <stdio.h>

/*
Write a program called lcp that prints on the standard output the maximal length 
of any common prefix in two or more of its command-line arguments. For example:
$ ./lcp ciao miao bao
0
$ ./lcp professor prefers to teach programming
3
*/

int main(int argc, char* argv []){

    int length = 0;

    int max = 0;

    for (int i = 1; i < argc; i ++){
        for (int j = i + 1; j < argc; j++){
            for(int k = 0; argv[i][k] != 0 && argv[j][k] != 0; k++){

                printf("arg1 =%c\n", argv[i][k]);
                printf("arg2 =%c\n", argv[j][k]);
                
                if (argv[i][k] == argv[j][k])   
                    length++;
                else break;
            }

            if (length > max)
            max = length;   
            length = 0;   
            printf("\n"); 
        } 
    }
    printf("%d\n", max);
}