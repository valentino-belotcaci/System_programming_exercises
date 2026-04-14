#include<stdio.h>

/*
Count Empty Lines
Write a C program called emptylines that counts and then outputs the number of empty lines in its standard input. 
As in the countlines exercise above, a line is defined as a sequence of zero or more 
characters terminated by the newline character '\n'.

Minimal testing
Test your program by writing some input files and then running your program with those files as the program’s standard input.


*/

int main(){

    int state = 1;
    int count = 0;
    int c = 0;

    while((c = getchar()) != EOF){
        if (state == 0  && c == '\n'){
            state = 1;
        }
        else if (state == 1 && c == '\n'){
            state = 1;
            count++;
        }
        else if (state == 1 && c != '\n'){
            state = 0;
        }
    }

    printf("%d\n", count);
}