#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {

    int k = 5;

    if (argc > 1)
        k = atoi(argv[1]);
    
    if (k > 100 || k < 1)
        return EXIT_FAILURE;

    char line [k][1001];
    int count = 0;
    int i = 0;

    while(fgets(line[i], 1001, stdin)){
        count++;
        i = (i + 1) % k;
    }

    if (count < k)
        return EXIT_FAILURE;

    for(int i = 0; i < k; i++){
        printf("%s", line[i]);
    }
}