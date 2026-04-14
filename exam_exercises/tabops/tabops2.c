#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH 1024

/* returns 1 if c is a delimiter, else 0 */
int is_delim(char c, const char *delim) {
    for (const char *d = delim; *d != 0; ++d)
        if (*d == c) return 1;
    return 0;
}


unsigned string_tokenize(char * str, const char *S[], const char * delim){

    int token = 0; //flag, 0 outside word(delimiter), 1 inside a word
    int num_words = 0;
    char * p;

    for (p = str; *p != 0; p++) {

        if (is_delim(*p, delim) == 1 || *p == '\n'){ // if p is a delimiter
            if (token == 1){
                *p = '\0';
                token = 0;
                if (num_words == 26)
		            return num_words;
            } 
        }

        else {
            if (token == 0){
                S[num_words++] = p;
                token = 1;
            }
        }

    }
    *p = 0;
    return num_words;

}


void process_file(char * format, char * delim, FILE * f){

    char line[LINE_LENGTH + 1];
    const char * S[26];
    
    while (fgets(line, LINE_LENGTH + 1, f)) {

        unsigned n = string_tokenize(line, S, delim);


        char * p = format;
        int state = 0;

        while(*p != 0 && *p != '\n'){
            if (*p != '@' && state == 0){
                state = 0;
                putchar(*p);
                p++;
            }
            else if (*p == '@' && state == 0){
                state = 1;
                p++;
            }
            else if(state == 1 && *p == '@'){
                state = 1;
                p++;
            }
            else if (state == 1 && (*p < 'a' || *p > 'z')){
                state = 0;
                p++;
            }
            else if (state == 1 && (*p >= 'a' && *p <= 'z' && *p != 'x')){

                int c = *p - 'a';
                if(c < n)
                    printf("%s", S[c]);
                p++;
                state = 0;

            }
            else if (state == 1 && (*p >= 'a' && *p <= 'z' && *p == 'x')){
                p++;
                state = 0;
            }
        }
        printf("\n");
    }

}


int main(int argc, char * argv[]) {

    char * format = "@a";
    char * delim = " \t";
    int file = 0;

    if (argc > 1){
        for (int i = 1; i < argc; i++){
            if (strncmp(argv[i], "format=", 7) == 0)
                format = argv[i] + 7;
            else if (strncmp(argv[i], "delim=", 6) == 0)
                delim = argv[i] + 6;
            else {
                file = 1;
                FILE * f = fopen(argv[i], "r");
                if (f == NULL){
                    printf("error opening file %s", argv[i]);
                    continue;
                }
                //printf("running ex with file %s, format %s, delim %s", argv[i], format, delim);
                process_file(format, delim, f);
                fclose(f);
            }
        }
    }

    if(file == 0)
        process_file(format, delim, stdin);


}