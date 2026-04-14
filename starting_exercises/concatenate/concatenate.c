#include<stdio.h>

/*
concatenate string: In a source file called concatenate.c write a function: 
int concatenate(char * s, unsigned max_size, const char * s2) The concatenate function must concatenate 
the string s2 to the string s making sure that the resulting string s does not contain more than max_size characters, 
including the terminator character. 
The concatenate function must return true (non zero) if and only if it concatenated the full 
second string s2 without exceeding the max_size limit. You may not use any external library function, 
not even from the C standard library.
*/


int concatenate(char * s, unsigned max_size, const char * s2){

    unsigned int size = 0;
    for(size = 0; s[size] != 0; size++);
        
    for(int i = 0; size + i < max_size; i++){
        s[size + i] = s2[i];
        if(s2[i] == 0)
            return 1;
    }
    s[max_size - 1] = 0;
    return 0;
}

