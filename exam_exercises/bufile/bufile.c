#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bufile.h"

struct bufile{
    char * begin;
    char * end;
};

typedef struct bufile BUFILE;


BUFILE * bufopen(char * begin, char * end){

    BUFILE * b = malloc(sizeof(BUFILE));
    
    if (!b)
        return NULL;

    b->begin = begin;
    b->end = end;

    return b;
}

void bufclose(BUFILE * buf){
    free(buf);
}

/*
The bufgets function is analogous to the fgets function from the standard I/O library.1
In particular, bufgets(s,size,bf) reads in at most one less than size characters from the buffer stream,
and stores them into the buffer pointed to by s. Reading stops when the file buffer stream ends or
after a newline. If a newline is read, it is stored into the buffer. A terminating null byte (’\0’) is
stored after the last character in the buffer. bufgets(s,size,bf) returns s on success, and NULL
on error or when the end of stream occurs while no characters have been read.
*/

char *bufgets(char *s, int size, BUFILE * buf){

    if (buf->begin == buf->end)
        return NULL;

    int i = 0;

    while(size - i > 1 && buf->begin != buf->end){

        char c = *buf->begin;
        s[i++] = c;
        buf->begin++;
        if (c == '\n') break;
    }
    
    s[i] = '\0';


    return s;
    
}
