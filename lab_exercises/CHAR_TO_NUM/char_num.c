#include<stdio.h>

/*
Reading and Writing Numbers
Write a C program called mimimum that reads a sequence of non-negative numbers and 
outputs the smallest one. If the input does not contain numbers, 
then the program must not output anything. Numbers are contiguous sequences of decimal digits, 
meaning characters '0', '1', …, '9' separated by any one or more other character. 
Your program may not use any external function other than the getchar() and putchar() library function.

For example, with the following input:

xxx123x121x111x124x
The program must produce the following output.

111
Notice that the decimal digit characters have consecutive numeric codes. 
The specific codes don’t matter. What matters is that the numeric code for '1' is 1 plus the numeric code 
for '0', '2' is 1 plus '1', and so on.
*/


static void put_int(unsigned int n)
{
    /* Collect digits in reverse order */
    char buf[10];                 /* enough for 0 … 4 294 967 295 on 32-bit */
    int  i = 0;

    if (n == 0) {                 /* special case: single zero */
        putchar('0');
        return;
    }

    while (n > 0) {
        buf[i++] = (char)('0' + (n % 10));
        n /= 10;
    }
    /* Output in correct order */
    while (i--)
        putchar(buf[i]);
}
/*

int main(){

    int min = 999999999;
    int found = 0;//if we found at least a number
    int number = 0;
    int c = 0;
    int state = 0;

    while((c = getchar()) != EOF){
        if (state == 0 && (c >= '0' && c <= '9')){
            found = 1;
            number = c - '0';
            //printf("num = %d\n", number);
            state = 1;
        }
        else if (state == 1 && (c >= '0' && c <= '9')){
            number = number * 10 + (c - '0');
            //printf("%d\n", number);
        }
        else if (state == 1 && (c < '0' || c > '9')){
            if(number < min){
                min = number;
                //printf("min = %d\n", min);
            }
            state = 0;
        }
    }

    if (state == 1){
        if (number < min)
            min = number;
    }

    if (found == 1){
        put_int(min);
        //printf("%d\n", min); //we couldnt use printf
        putchar('\n');
    }

}*/

int main() {

    int c;
    int minimum = 99999999;
    int state = 0;
    int number = 0;
    int prev = 0;
    int found = 0;

    // step 1 getchar with state machine to get the number
    while ((c = getchar()) != EOF){
        if (state == 0 && (c < '0' || c > '9')){
            state = 0;
        }
        else if (state == 0 && (c > '0' && c < '9')){
            number = c - '0';
            found = 1;
            //printf("%d", number);
            state = 1;
        }
        else if (state == 1 && (c > '0' && c < '9')){
            number = number * 10 + c - '0';
            state = 1;
        }
        else if (state == 1 && (c < '0' || c > '9')){
            if (number < minimum)
                minimum = number;
            prev = number;
            state = 0;
        }
    }

    if (state == 1 && number < minimum)
        minimum = number;
        
    printf("%d", minimum);
    // step 2 compare the number with the previous one 
    // step 3 repeat

}

