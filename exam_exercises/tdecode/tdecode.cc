#include <iostream>
#include <map>
#include <cctype>


int main(){

    int firstByte = getchar();
    std::map<int, std::string> codes;

    int c = 0;

    if(firstByte == EOF)
        return EXIT_SUCCESS;

    if (firstByte < 128){
        putchar(firstByte);
        while((c = getchar()) != EOF){
            putchar(c);
        }
    }

    else{

        int byte = firstByte;
        //std::cout << byte <<std::endl;
        int c = 0;
        int state = 1;
        std::string w;

        while((c = getchar()) != EOF && c != '\n'){
            
            if (c < 128){
                state = 1;
                w.push_back(c);
            }
            else if (state == 1 && c > 127){
                codes[byte] = w;
                w.clear();
                //std::cout << byte <<std::endl;
                byte = c;
                //std::cout << byte <<std::endl;
                state = 0;
            }
        }
        if(state == 1){
            codes[byte] = w;
            w.clear();
            state = 0;
        }

    }
/*
    for(auto& pair : codes){
        std::cout << pair.first << " " << pair.second << std::endl;
    }*/

    while((c = getchar()) != EOF){
        if (c > 127){
            for(auto& pair : codes){
                if(pair.first == c)
                    std::cout << pair.second;
            }

        }
        else    
            putchar(c);
    }

}