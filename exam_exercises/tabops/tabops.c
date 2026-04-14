#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_delim(char c, char * delim){

    for(char * ch = delim; *ch != 0; ch++){
        if(*ch == c)
            return 1;
    }
    return 0;
}

void process_file(char * format, char * delim, FILE * f ){

    char line[1025];



    while (fgets(line, sizeof(line), f)){
        char * S [26];

        for(int i = 0; i < 26; i++){
            S[i] = NULL;
        }
        int n = 0;
        char * start = line;
        char * end = line;

        int state = 0;

        while (*end != 0){
            unsigned char c = (unsigned char) *end;

            if (state == 0 && (is_delim(c, delim) == 0 && c != '\n')){
                state = 1;
                start = end;
            }
            else if (state == 1 && (is_delim(c, delim) == 1 || c == '\n')){
                state = 0;
                char saved = *end;
                *end = 0;
                if (n < 26)
                    S[n++] = strdup(start);
                *end = saved;
            }
            end++;
        }
        if (state == 1){
            char saved = *end;
            *end = 0;
            if (n < 26)
                S[n++] = strdup(start);
            *end = saved;
        }
    
        char *p = format;

        while(*p != 0){
            if(*p == '@'){
                p++;
                if((*p >= 'a' && *p <= 'z') && *p != 'x'){
                    int byte = *p - 'a';
                    if(byte < n)
                        printf("%s", S[byte]);
                }
                else putchar('@');
            }
            else putchar(*p);
            p++;
        }
        putchar('\n');

        for(int i = 0; i < n; i++){
            free(S[i]);
    }

    }

    /*
    for(int i = 0; i < n; i++)
        printf("%s\n", S[i]);
    */

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