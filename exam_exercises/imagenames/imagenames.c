#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * find_last_slash(char * doc){

    char * last_slash = doc;
    int found = 0;

    while (*doc != 0){

        if (*doc != '/') 
            doc++;
        else{
            found = 1;
            last_slash = doc;
            doc++;
        }
    }
    return found == 1 ? ++last_slash : last_slash;
}


char * find_last_point(char * doc){

    char * last_point = doc;

    while (*doc != 0){

        if (*doc != '.') 
            doc++;
        else{
            last_point = doc;
            doc++;
        }
    }
    return last_point;

}

int main(int argc, char * argv[]) {

    char * extensions [] = {".jpeg", ".jpg", ".png", ".tif", ".tiff"};
    char * extensions_file [1000] = {NULL};

    char line[1001];
    int j = 0;

    if (argc > 1){
        FILE * f = fopen(argv[1], "r");
        if (f != NULL){
            while(fgets(line, 1001, f)){
                line[strcspn(line, "\n")] = 0; // rimuove newline
                extensions_file[j] = malloc(strlen(line) + 1);
                if (extensions_file[j] != NULL) {
                    strcpy(extensions_file[j], line);
                    j++;
                }
            }
            fclose(f);
        }
    }

    while(fgets(line, 1001, stdin)){
        line[strcspn(line, "\n")] = 0; // rimuove newline

        char * begin = find_last_slash(line);
        char * end = find_last_point(begin);

        int n_extensions = (argc == 1) ? sizeof(extensions) / sizeof(extensions[0]) : j;

        for(int i = 0; i < n_extensions; i++){
            char * p = end;
            char * p2 = (argc == 1) ? extensions[i] : extensions_file[i];

            if (p == NULL || p2 == NULL)
                continue;

            if (strcmp(p, p2) == 0){// or while p != p2
                *p = '\0'; // tronca l'estensione
                printf("%s\n", begin);
                break;
            }
        }
    }

    // libera memoria
    if (argc > 1) {
        for (int i = 0; i < j; i++) {
            free(extensions_file[i]);
        }
    }

    return 0;
}
