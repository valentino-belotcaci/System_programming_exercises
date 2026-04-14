#include<stdio.h>
#include<stdlib.h>
/*
volumes: Write a C program called volumes that takes an integer V as a command-line argument, 
and then reads from the standard input a set of triples of integers representing the width, 
height, and depth of a container. The program must output the number of containers whose volume is at least V.
*/

int main(int argc, char * argv[]){

    int V = atoi(argv[1]);

    float width, height, depth;

    int c = 0;
    
    while (scanf("%f %f %f", &width, &height, &depth) == 3){

        if(width * height * depth >= V)
            c++;
    }

    printf("%d\n", c);
}