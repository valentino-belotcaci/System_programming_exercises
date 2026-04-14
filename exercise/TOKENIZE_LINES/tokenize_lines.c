#include<stdio.h>


int count(){
    static int c = 0;//initialization, not assignment
    return c++;
}


/* returns 1 if c is a delimiter, else 0 */
int is_delim(char c, const char *delim) {
    for (const char *d = delim; *d != 0; ++d)
        if (*d == c) return 1;
    return 0;
}

char * string_tokenize(char * str, const char *delim) {
    static char *next = NULL;  
    
    if (str != NULL) next = str;

    if (next == NULL) return NULL;

    // skip delimiters
    while (*next != '\0' && is_delim(*next, delim)) {
        next++;
    }
    if (*next == '\0') return NULL;

    char *start = next;
    while (*next != '\0' && !is_delim(*next, delim)) {
        next++;
    }

    if (*next != '\0') {
        *next = '\0';
        next++;
    }
    return start;
}

unsigned string_tokenize(char * str, const char *S[], const char * delim){

    int token = 0; //flag, 0 outside word(delimiter), 1 inside a word
    int num_words = 0;
    char * p;

    for (p = str; *p != 0; p++) {

        if (is_delim(*p, delim) == 1){ // if p is a delimiter
            if (token == 1){
                *p = '\0';
                token = 0;
            } 
        }

        else {
            if (token == 0){
                S[num_words++] = p;
                token = 1;
            }
        }

    }
    return num_words;

}



int main(int argc, char *argv[]){
    /* Delimiters: default " \t\n". If an arg is given, use that + '\n' only. */
    char delim_buf[256];
    const char *delim;

    if (argc > 1) {
        /* newline is always a delimiter */
        snprintf(delim_buf, sizeof(delim_buf), "%s\n", argv[1]);
        delim = delim_buf;
    } else {
        delim = " \t\n";
    }

    char line[4096];
    const char *S[1024];
    int line_num = 0;

    while (fgets(line, sizeof(line), stdin)){
        ++line_num;
        unsigned n = string_tokenize(line, S, delim);
        for (unsigned i = 0; i < n; ++i)
            printf("%d,%u:%s\n", line_num, i+1, S[i]);
    }
}