#include <stdio.h>
#include <ctype.h>

/*
wordcount: Write a C program called wordcount that counts the words in the standard input. 
A word is a sequence of one or more characters delimited by white space. 
(Hint: there is a standard function to check whether a character is "white space".) 
The output should be the same as the command: wc -w.
*/

int main(){

    int state = 0;
    int c = 0;
    int words = 0;

    while((c = getchar()) != EOF){

        if (state == 0 && !isspace(c)){
            state = 1;
            words++;
        }
        else if (state == 0 && isspace(c))
            state = 0;
        else if (state == 1 && !isspace(c))
            state = 1;
        else
            state = 0;
            
    }
    
    printf("%d\n", words);
}