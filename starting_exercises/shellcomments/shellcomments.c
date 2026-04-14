#include<stdio.h>

/*
shellcomments: Write a C program called shellcomments that reads a shell script from the standard input, 
and prints on the standard output the comments in the input script. Recall that a comment is the text following 
the pound character ('#') up to the end of line, including the new-line character ('\n'). 
The output should be the same as the command: sed -n -e 's/^[^#]*#//p'
*/

int main(){

    int state = 0;
    int c = 0;

    while((c = getchar()) != EOF){
        if(state == 1 && c == '\n'){
            putchar(c);
            state = 0;
        }
        else if (c == '#' && state == 0)
            state = 1;
        else if (state == 1)
            putchar(c);
    }
}