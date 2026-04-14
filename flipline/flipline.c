#include<stdio.h>
#include<string.h>

/*
flipline: Write a C program called flipline that reads a text file from the standard input, 
and prints each line in reverse order. For example, for an input line containing the characters ciao, 
the program should output oaic. Notice that the output must have exactly the same number of lines as the input. 
In particular, If an input line is terminated by a newline character ('\n'), 
then the output line should also be terminated by a newline character. 
Otherwise, if the input line is terminated by the end of file, 
then the output line should also terminate the file directly (without a newline character). 
You may assume that lines are at most 1000 characters long (bytes).
*/

int main(){
    char line[1001];
    int flag = 0;//used for endofline

    while(fgets(line, 1001, stdin)){    
        int len = strlen(line) - 1;

        if(line[len] == '\n'){
            flag = 1;
            len = len - 1;
        }

        for(int i = len; i >= 0; i--)
            putchar(line[i]);

        if(flag == 1)
            putchar('\n');

        flag = 0;
    }

}
