#include <stdio.h>
#include <string.h>
#include <ctype.h>



int main(){

    char line[1001];

    while(fgets(line, sizeof(line), stdin)){
        int state = 0;
        char * start = line;
        char * end = line;
        int count = 0;

        while (*end != 0){
            unsigned char c = (unsigned char) *end;
            if (state == 0 && isalpha(c)){
                state = 1;
                start = end;
            }
            else if (state == 1 && !isalpha(c)){
                char saved = *end;
                *end = 0;
                char * word = strdup (start);
                *end = saved;
                printf("%s\n", word);
                count++;
                state = 0;
            }
            end++;
        }
        if (state == 1){
            count++;
        }

        printf("%d\n", count);
    }
}
