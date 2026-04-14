#include<stdio.h>
#include<string.h>
/*
top color: Write a program called topcolor in a source file called topcolor.c. 
The program must reads a text file consisting of lines each specifying the dimensions (width and height) 
and the color of a rectangle. The program must output the color of the largest rectangle. 
A color is a string that is guaranteed to be shorter than 20 characters. For example, with the following input
10 20 blue
15 15 green
12 8 red
the output must be
green
If there are two or more maximal rectangles, then the program should output the color of the first one. 
You may not use any external library function other than the input functions from the C standard library.
*/

int main(){

    int flag = 0;
    float w, h;
    char color[21];
    float area = 0;
    float max = 0;
    char color_big [21] = "";
    
    while (scanf("%f %f %s", &w, &h, color ) == 3){
        flag = 1;
        area = (w * h) / 2;

        if (area > max){

            max = area;

            int i = 0;

            //strcpy(color_big, color); the while does the same

            while(color[i] != 0){
                color_big[i] = color[i];
                i++;
            }
            color_big[i] = '\0';
        }
    }
    if(flag == 1)
        printf("%s\n",color_big);
}