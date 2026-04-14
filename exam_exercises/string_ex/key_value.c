#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Pair {
    char * key;
    char * value;
    struct Pair * next;
};

struct Pair * pairs = 0;

struct Pair * add_pair (char * key, char * value){
    struct Pair * p = malloc(sizeof(struct Pair));
    p->key = key;
    p->value = value;
    p->next = pairs;
    pairs = p;
    return p;
}

int main(){

    char line[1001];

    char * key;
    char * value;

    while(fgets(line, sizeof(line), stdin)){

        char * start = line;
        char * end = line;

        int state = 0;

        while(*end){
            unsigned char c = (unsigned char)*end;

            if (state == 0) {
                if (!isspace(c)) { state = 1; start = end; } // inizio key
            }
            else if (state == 1) { 
                if (c == '=') {
                    char saved = *end; 
                    *end = 0;
                    key = strdup(start);
                    *end = saved;
                    state = 2;
                    start = end + 1; 
                }
                // opzionale: se incontri spazio prima di '=', errore/ignora
            }
            else if (state == 2) { // leggendo value
                if (isspace(c)) {
                    char saved = *end;
                    *end = 0;
                    value = strdup(start);
                    *end = saved;
                    struct Pair * p = add_pair(key, value);
                    printf("key : %s, Value : %s\n", key, value);
                    state = 0;
                }
            }
            end++;
        }

        if(state == 1){
            char saved = *end;
            *end = 0;
            value = strdup(start);
            *end = saved;
            struct Pair * p = add_pair(key, value);
            printf("key : %s, Value : %s\n", key, value);
            state = 0;
        }
    }
}