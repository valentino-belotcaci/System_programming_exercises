#include <vector>
#include <algorithm>
#include <iostream>


int is_delimiter(char c, const char *delim) {
    int res = 0;
    for(const char *p = delim; *p != 0; p++){
        if(*p == c){
            res = 1;
            return res;
        }
    }
    return res;
}



int main(){

    const char *delim = "\n/,;";
    std::string line;

    while (std::getline(std::cin, line)){
        auto start = line.begin();
        auto end = line.begin();
        int state = 0;

        while (end != line.end()){
            unsigned char c = (unsigned char) * end;

            if (state == 0 && is_delimiter(c, delim) == 0){

                start = end;
                state = 1;
            }
            else if (state == 1 && is_delimiter(c, delim) == 1){
                std::string w(start,end);
                std::cout << w << std::endl;
                state = 0;
            }
            end++;
        }

        if (state == 1){
            std::string w(start,end);
            std::cout << w << std::endl;
        }
    }
}