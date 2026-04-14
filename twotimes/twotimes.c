#include<stdio.h>

/*
twotimes: In a source file called twotimes.c write two functions, int twotimes(const char *s) 
and int twotimes2(const char *begin, const char *end), that return true (non zero) if the string passed 
as argument consists of the concatenation of two identical strings, or false (zero) otherwise. 
The twotimes function takes a C-string, meaning a zero-terminated string. 
The twotimes2 function takes any sequence of chars defined by a pointer to the first character (begin) 
and a pointer to first character past the end of the string (end). You may not use any external library function, 
not even from the C standard library.
*/


int twotimes(const char *s){
    const char *p = s;
    int length = 0;

    while(*p != 0){
        length++;
        p++;
    }

    if (length % 2 != 0)
        return 0;

    else{
        p = s;
        const char *comp = s + length / 2;
        //printf("%s\n", comp);
        //printf("%s\n", p);

        while(*comp != 0){
            //printf("%c\n", *comp);
            //printf("%c\n", *p);
            if(*comp == *p){
                comp++;
                p++;
            }
            else return 0;
        }
    }
    return 1;
}

int twotimes2(const char *begin, const char *end){

    const char * p = begin;
    int length = 0;

    while(p != end){
        p++;
        length++;
    }

    if (length % 2 != 0)
        return 0;

    p = begin;
    
    const char *p2 = begin + length / 2;

    while(p2 != end){

        if(*p2 == *p){
            p++;
            p2++;
        }

        else return 0;
    }
    return 1;

}

/*
int main(){
    int res = 0;
    const char *s = "aba";
    res = twotimes2(s, s + 4);
    printf("%d", res);
}
*/