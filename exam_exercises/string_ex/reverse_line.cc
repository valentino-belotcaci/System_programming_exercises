#include <vector>
#include <algorithm>
#include <iostream>
#include <map>


int main(){
    std::string line;

    while (getline(std::cin, line)){
        int state = 0;
        auto start = line.begin();
        auto end = line. begin();

        while(end != line.end()){
            unsigned char c = (unsigned char) *end;

            if (state == 0 && !isalpha(c)){
                std::cout << c;
            }
            if (state == 0 && isalpha(c)){
                state = 1;
                start = end;
            }
            else if (state == 1 && !isalpha(c)){
                std::string w(start,end);
                //unsigned char b = (unsigned char) *end;
                for(auto it = w.end(); it >= w.begin(); it--){
                    unsigned char b = (unsigned char ) * it;
                    std::cout << b;
                }
                std::cout << c;
                state = 0;
            }
            end++;
        }
        if(state == 1){
            std::string w(start,end);
            //unsigned char b = (unsigned char) *end;
            for(auto it = w.end(); it >= w.begin(); it--){
                unsigned char b = (unsigned char ) * it;
                std::cout << b;
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}