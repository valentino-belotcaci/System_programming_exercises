#include<stdio.h>

/*
Count Lines
Write a C program called linecount that counts lines in the standard input. 
A line is any sequence of zero or more characters terminated by the newline character '\n'. 
The output is the number of lines.

Minimal testing
Test your program by writing some input files and then running your 
program with those files as the program’s standard input.
*/


int main(){

    int count = 0;

    int c = 0;

    while((c = getchar()) != EOF ){

        if(c == '\n')
            count++;

    }

    printf("%d\n", count);
}