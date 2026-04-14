#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(){

    char line [1001];

    int sum;

    while(fgets(line, sizeof(line), stdin)){
        char *end = line;
        int state = 0;

        char sign;
        int num = 0;
        int sum = 0;

        while (*end != 0){
            unsigned char c = (unsigned char ) *end;

            if (state == 0 && (c == '-' || c == '+')){
                sign = c;
                state = 1;
            }
            else if (state == 0 && isdigit(c)){
                state = 2;
                num = (c - '0');
            }
            else if(state == 1 && isdigit(c)){
                state = 2;
                if(sign == '-')
                    num = (c - '0') * -1;
                else num = (c - '0') ;
            }
            else if(state == 1 && !isdigit(c)){
                state = 0;
            }
            else if (state == 2 && isdigit(c)){
                num = num * 10 + (c - '0');
            }
            else if (state == 2 && !isdigit(c) && (c == '-' || c == '+')){
                state = 1;
                sign = c;
                sum += num;
            }
            else if (state == 2 && !isdigit(c) && (c != '-' && c != '+')){
                state = 0;
                printf("%d\n", num);
                sum += num;
            }
            else if (state == 1 && !isdigit(c)){
                state = 0;
            }
            end++;
        }
        if (state == 2) {
            sum += num;
        }
        printf("%d\n", sum);
    }
}