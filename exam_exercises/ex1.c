#include <stdio.h>

/*
The function print_numbers must print on the standard output all the numbers in the input
string, each on an individual line. A number is a contiguous sequence of digits (characters ’0’,
. . . , ’9’) possibly preceded by a sign (characters ’-’ or ’+’). The function returns the total count
of numbers printed. Write your implementation in a file called print_numbers.c.
*/

int print_numbers(const char * input){

    int state = 0;
    int c = 0;
    int number = 0;
    int total_n = 0;
    char symbol;

    for (const char * c = input; *c != 0; c++){

        if(state == 0 && (*c >= '0' && *c <= '9')){
            state = 2;
            number = *c - '0';
        }
        else if (state == 0 && (*c == '+' || *c == '-')){
            state = 1;
            symbol = *c;
        }
        else if (state == 1 && (*c == '+' || *c == '-')){
            state = 1;
            symbol = *c;
        }
        else if (state == 1 && (*c != '+' && *c != '-') && (*c < '0' || *c > '9'))
            state = 0;
        else if (state == 1 && (*c >= '0' && *c <= '9')){
            state = 2;
            putchar(symbol);
            number = *c - '0';
        }
        else if (state == 2 && (*c >= '0' && *c <= '9')){
            number = number * 10 + *c - '0';
        }
        else if (state == 2 && (*c == '+' || *c == '-')){
            state = 1;
            total_n++;
            symbol = *c;
            printf("%d\n", number);
        }
        else if (state == 2 && (*c < '0' || *c > '9')){
            state = 0;
            total_n++;
            printf("%d\n", number);
        }

    }

    if (state == 2){          
        total_n++;
        printf("%d\n", number);
    }
    
    return total_n;

}

int main(){
    int tot = 0;
    const char * str = "+1aab-+12fda2d34aa-aa2io32+1";

    tot = print_numbers(str);

    printf("tot = %d\n", tot);
}