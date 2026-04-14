#include<stdio.h>

/*
redact digits: Write a function int redact_digits(char *s) in a C source file called redactdigits.c 
that modifies the string passed as input so as to redact the appearence of every digit in the string. 
Redacting means replacing every digit with the hash mark ('#'). 
The return value must be 1 if the input string was modified, or 0 otherwise.
*/

int redact_digits(char *s){

    int flag = 0;

    while (*s != 0){
        if(*s >= '0' && *s <= '9'){
            *s = '#';
            flag +=1;
        }
        s++;
    }

    if (flag == 0)
        return 0;
    return 1;

}

/*
int main(){
    int res = 0;

    char str[] = "ciao1";           // copia locale scrivibile
    res = redact_digits(str);
    printf("%d\n", res);            // Output: 1
    printf("%s\n", str);            // Output: ciao#

}
*/