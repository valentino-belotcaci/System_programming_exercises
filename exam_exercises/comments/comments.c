#include <stdio.h>
#include <string.h>
#include <ctype.h>

void check_comments(FILE * f, char * filename, char * separator){

    char line[1001];
    int pure_lines = 0;
    int num_lines = 0;

    while(fgets(line, 1001, f)){
        int i = 0;

        num_lines++;

        char * sep2 = separator;

        while (isspace(line[i]))
            i++;

        while (line[i] == *sep2){
            i++;
            sep2++;
        }

        if (*sep2 == 0){
            pure_lines += 1;
        }
    }
    printf("%s\t%d\t%d\n", filename, pure_lines, num_lines);
}


int main(int argc, char * argv[]) {

    char * comment = "//";
    int file = 0;

    if (argc > 1){

        for (int i = 1; i < argc; i++)

            if (strncmp(argv[i], "comment=", 8) == 0)
                comment = argv[i] + 8;

            else{
                file = 1;
                FILE * f = fopen(argv[i], "r");
                if (f == NULL){
                    printf("error opening file %s", argv[i]);
                    continue;
                }
                check_comments(f, argv[i], comment);
                fclose(f);
            }
    }

    //printf("%s\n", comment);

    if (file == 0)
        check_comments(stdin, "(stdin)", comment);
}