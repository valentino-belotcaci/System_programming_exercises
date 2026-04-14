#include <stdio.h>
#include <stdlib.h>
/*
Longest Common Prefix for All Arguments
Write a program called lcp4a that prints on the standard output the maximal length of 
the prefix that is common between all its command-line arguments. For example:

$ ./lcp4a ciao miao bao
0
$ ./lcp4a professor prefers to teach programming
0
$ ./lcp4a professor prefers programming
2
*/

int main(int argc, char * argv[]){

    int length = 0;
    int min = 9999;

    for (int i = 1; i < argc; i ++){
        for (int j = i + 1; j < argc; j++){
            for(int k = 0; argv[i][k] != 0 && argv[j][k] != 0; k++){

                printf("arg1 =%c\n", argv[i][k]);
                printf("arg2 =%c\n", argv[j][k]);
                
                if (argv[i][k] == argv[j][k])   
                    length++;

                else if (length == 0){
                    printf("0\n");
                    return EXIT_FAILURE;
                }
                else break;
            }

            if (length < min)
                min = length;   
            length = 0;   
            printf("\n"); 
        } 
    }
    printf("%d\n", min);
}