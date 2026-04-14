#include <stdio.h>

/*
Compress Spaces
Write a C program called compress_spaces that reads text from standard input, 
and outputs the same text formatted as follows:

There are no horizontal spaces at the beginning of a line.
There are no horizontal spaces at the end of a line, before the end-of-line byte.
Every sequence of two or more horizontal space characters between non-space characters
is printed as a single space character (' ').
An horizontal space character is either a space character (' ') or a tabulation character ('\t').


*/

int main(){

    int state = 0;
    int c = 0;

    while((c = getchar()) != EOF){
        if ((state == 1 && c != ' ') || state == 0 && c != ' '){
            putchar(c);
            state = 1;
        }
        else if  (state == 1 && c == ' ')
            state = 2;
        else if (state == 2 && c == '\n'){
            state = 0;
            putchar(c);
        }
        else if (state == 2 && c != ' '){
            putchar(' ');
            putchar(c);
            state = 1;
        }
        
    }

}