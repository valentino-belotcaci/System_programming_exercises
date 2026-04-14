#include<stdio.h>

/*
statistics: Write a C program in a source file called statistics.c that reads a sequence of numbers, and outputs, 
on a single line, the minimum value, the average value, and the maximum value. 
Every value must be printed as a floating-point number with exactly six digits after the decimal point. 
You may assume that the format of the input stream is correct, 
meaning that the input consists of a sequence of numbers separated by white space. 
However, the input may contain no numbers at all, in which case, the output must be empty.
*/

int main(){
    float num = 0;
    float c = 0;
    float min = 0;
    float sum = 0;
    float max = 0;

    while(1){

        if (scanf("%f", &num) == 1){
            if (c == 0){
                min = max = num;            
            }

            if (num < min)  min = num;
            
            if (num > max)  max = num;

            sum += num;

            c++;
        }

        else break;
    }

    if (c != 0)
        printf("%f %f %f\n", min, sum / c, max);
}