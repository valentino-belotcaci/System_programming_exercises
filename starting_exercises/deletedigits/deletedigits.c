#include<stdio.h>

/*
delete digits: Write a function int delete_digits(char *s) in a C source file called deletedigits.c 
that modifies the string passed as input so as to delete every digit in the string. 
The return value must be 1 if the input string was modified, or 0 otherwise.
*/


/*
Diciamo che hai questa stringa:

char s[] = "c1a2o";   // buffer scrivibile
Quindi:

inizialmente r = w = s → entrambi puntano a 'c'

il primo carattere ('c') non è una cifra → fai *w = *r e poi w++, r++
→ 'c' resta dov'è

il secondo carattere ('1') è una cifra → r++ ma niente copia → '1' verrà sovrascritto più tardi

r ora punta a 'a' → *w = *r copia 'a' sopra la posizione dove c'era '1'

e così via…

A ogni passo, *w = *r serve per ricompattare la stringa, facendo “scivolare” a sinistra solo i caratteri validi.
*/

int delete_digits(char *s){

    char * w = s;//write pointer, write chars that we want
    char * r = s;
    int flag = 0;

    while (*r != 0){

        if(*r < '0' || *r > '9'){
            *w = *r;
            w++;
        }
        else 
            flag = 1;
        r++;
    }
    *w = '\0';

    return flag;
}
/*
int main(){
    int res = 0;
    char s[] = "ciao";
    res = delete_digits(s);
    printf("%d", res);
    printf("%s", s);
}
*/