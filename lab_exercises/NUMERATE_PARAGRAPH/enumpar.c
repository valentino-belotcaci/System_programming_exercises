#include<stdio.h>

/*
Write a C program called enumpar that reads a text from its standard input, and copies 
the text onto its standard output by formatting and enumerating each paragraph. 
A paragraph is a maximal contiguous sequence of one or more non-empty lines. 
The program must output each paragraph indented by six spaces, with a counter printed at the 
beginning of the first line of each paragrah. More specifically, the text of each line of a paragraph 
(non-empty, by definition) starts at column 6, and the first line of the paragraph also contains the 
paragraph counter printed as a number right-aligned to column 5.

Paragraph in the input may be separated by one or more lines. 
However, the output paragraphs must be separated by a single empty line. The paragraph counter starts at 1.
*/

int main() {

    int count = 1;
    int flag = 0;
    int c = 0;

    char line[1001];

    while (fgets(line, 1001, stdin)){
        
        if(line[0] != '\n' && flag == 0){
            printf("%d", count);
            printf("  %s", line);
            flag = 1; //we are in a paragraph
        } 
        else if(flag == 1 && line[0] != '\n')
            printf("   %s", line);

        if (flag == 1 && line[0] == '\n'){
            flag = 0;
            count++;
            printf("\n");
        }
    }

    printf("\n");
}