#include <stdio.h>
#include <string.h>

/*
contains string: In a source file called containstr.c write a function int contains_str(const char * s, const char * x) 
The contains_str function must return true (non zero) if and only if the string s contains the string x. 
You may not use any external library function, not even from the C standard library.
*/

int contains_str(const char * s, const char * x){

    int word_len = strlen(x);
    //printf("wordlen = %d\n", word_len);

    if (strlen(s) < word_len)
        return 0;
    if (word_len == 0)
        return 1;

    const char * p = x;

    int count = 0;//used to count the number of consecutive equal chars

    int state = 0;
    
    while(*s != 0 && *p != 0){
        if (state == 0 && *s != *p){
            state = 0;
            s++;
        }
        else if(state == 0 && *s == *p){
            state = 1;
            s++;
            p++;
            count++;
            if(count == word_len)
                return 1;
            //printf("%d\n", count);
        }
        else if(state == 1 && *s == *p){
            state = 1;
            s++;
            p++;
            count++;
            //printf("%d\n", count);
            if(count == word_len)
                return 1;
        }
        else if (state == 1 && *s != *p){
            state = 0;
            count = 0;
            p = x;
            s++;
        }

    }
    return 0;
    

}


/*PROFESSOR SOLUTION
int string_prefix(const char * s, const char * p) {
    while (*p != 0) {
	if (*p != *s)
	    return 0;
	++p;
	++s;
    }
    return 1;
}

int contains_str(const char * s, const char * x) {
    if (*x == 0)
	return 1;
    
    while (*s != 0) {
	if (string_prefix(s, x))
	    return 1;
	++s;
    }
    return 0;
}


*/

/*
int main(){
    const char * s = "ciao";
    const char * x = "ciao";

    int res = 0;

    res = contains_str(s, x);
    printf("%d\n", res);
}*/