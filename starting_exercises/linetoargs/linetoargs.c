#include <stdio.h>
#include <string.h>

/*
linetoargs: In a source file called linetoargs.c write a function 
int line_to_args (char * argv[], int max_count, char * line) that takes an argument vector argv of maximal 
length max_count and a string line containing a sequence of zero or more arguments separated by one or more space characters.
The function must parse the input line, change the line, and set the argv vector to point to all the component arguments. 
The return value is the total number of arguments read and set in argv, which must always be less than or equal to max_count. 
For example, with a line "one two three" and an argument vector of at most 10 elements, 
the result is 3 and the 3 arguments are "one", "two", and "three", respectively. 
You must nt allocate additional memory. You may not use any external library function, not even from the C standard library.
*/

int line_to_args (char * argv[], int max_count, char * line){
    int j = 0;
    int len = strlen(line) - 1;
    for (int i = 0; i < len; i++) {

        while (line[i] == ' ' && i < len) {
            i++;  // skip all spaces
        }

        if (i >= len) break; // end of string reached after skipping spaces

        // Now we're at the beginning of a word
        argv[j++] = &line[i];

        // move forward until next space or end
        while (i < len && line[i] != ' ') {
            i++;
        }

        // null-terminate the word
        if (i < len) {
            line[i] = '\0';
        }
    }
    return j;
}
/*
int main(int argc, char * argv[]){
    char line[] = "one two three four";      // ✅ Writable array
    char *args[10];                     // ✅ Your own argv-like array

    int arg_count = line_to_args(args, 10, line);

    printf("Found %d arguments:\n", arg_count);
    //for (int i = 0; i < arg_count; i++) {
        //printf("%s\n", args[i]);

}*/