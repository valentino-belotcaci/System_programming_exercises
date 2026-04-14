#include <stdio.h>


/*
Longest Argument
Write a program called longest_argument that prints the longest command-line argument you pass to it. 
If there are more than one maximal arguments, the program must print the first one (leftmost).
*/

int main(int argc, char * argv[]){

    int count = 0;
    int max = 0;
    char * argument = "";

    for (int i = 1; i < argc; i++){
        for (int j = 0; argv[i][j] != 0; j++){
            count++;
        }
        if (max < count){
            max = count;
            argument = argv[i];
        }
        count = 0;
    }

    printf("%s\n", argument);
}