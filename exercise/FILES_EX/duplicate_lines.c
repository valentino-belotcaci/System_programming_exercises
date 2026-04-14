#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_lines(int d, int u, int n, FILE * f, char * filename){

    char line [100][1001];

    int i = 0;

    while(fgets(line[i], 1001, f)){
        i++;
    }
    
    if (d == 1){
        char duplicate [1001] = "";
        for (int j = 0;  j < i - 1; j++){
            if (strcmp(line[j], line[j + 1]) == 0 && strcmp(duplicate, line[j]) != 0){
                strcpy(duplicate, line[j]);
                if (n == 0)
                    printf("%s", line[j]);
                else
                    printf("%s:%d:%s", filename, j + 1, line[j]);
                }
        }
    }

    else if (u == 1){
        for (int j = 0;  j < i ; j++){
            if (j == 0) {
                if (strcmp(line[j], line[j + 1]) != 0){
                    if (n == 0)
                        printf("%s", line[j]);
                    else
                        printf("%s:%d:%s", filename, j + 1, line[j]);
                }
            }
            else if (j == i - 1){
                if (strcmp(line[j], line[j - 1]) != 0){
                    if (n == 0)
                        printf("%s", line[j]);
                    else 
                        printf("%s:%d:%s", filename, j + 1, line[j]);
                }
            }
            else if (strcmp(line[j], line[j + 1]) != 0 && strcmp(line[j], line[j - 1]) != 0){
                if (n == 0)
                    printf("%s", line[j]);
                else    
                    printf("%s:%d:%s", filename, j + 1, line[j]);
            }
        }
    }

}

int main(int argc, char * argv[]) {

    int d = 1;
    int file = 0;
    int u, n = 0;

    if (argc == 1){
        print_lines(d, u, n, stdin, "{stdin}");
        return EXIT_SUCCESS;
    }

    else {

        d = 0;

        for (int i = 1; i < argc; i++){
            if (strcmp(argv[i], "-d" ) == 0)
                d = 1;
            else if (strcmp(argv[i], "-u" ) == 0)
                u = 1;
            else if (strcmp(argv[i], "-n" ) == 0)
                n = 1;
            else {
                file  = 1;
                FILE * f = fopen(argv[i], "r");
                if (f == NULL){
                    printf("error opening file %s", argv[i]);
                    continue;
                }
                print_lines(d, u, n, f, argv[i]);
                fclose(f);
            }
        }
    }

    if (file == 0)
        print_lines(d, u, n, stdin, "{stdin}");
}