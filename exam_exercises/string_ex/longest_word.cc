#include <vector>
#include <algorithm>
#include <iostream>
#include <map>


int main(){

    std::string line;
    std::string word;
    std::string longest;

    int state = 0;

    while (std::getline(std::cin, line)){
        auto start = line.begin();
        auto end = line.begin();

        while (end != line.end()){
            unsigned char c = (unsigned char) *end;
            if (state == 0 && isalpha(c)){
                word.push_back(c);
                start = end;
                state = 1;
            }
            else if(state == 1 && isalpha(c)){
                word.push_back(c);
            }
            else if (state == 1 && !isalpha(c)){
                //std::cout << w << std::endl;
                if (word.size() > longest.size()){
                    longest = word;
                }
                word.clear();
                state = 0;
            }
            end++;
        }
        if (state == 1){
            if (word.size() > longest.size()){
                longest = word;
            }
            state = 0;
        }
    }
    std::cout << longest << " " << longest.size() << std::endl;
}
/*
int main(){
    int max = 0;

    std::string line;
    std::string word;

    while (std::getline(std::cin, line)){
        auto start = line.begin();
        auto end = line.begin();
        int state = 0;

        while (end != line.end()){
            unsigned char c = (unsigned char) *end;
            if (state == 0 && isalpha(c)){
                start = end;
                state = 1;
            }
            else if (state == 1 && !isalpha(c)){
                std::string w(start,end);
                //std::cout << w << std::endl;
                if (word.size() < w.size()){
                    word = w;
                }

                if(end - start > max)
                    max = end - start;
                state = 0;
            }
            end++;
        }
        if (state == 1){
            std::string w(start,end);
            //std::cout << w << std::endl;
            if (word.size() < w.size()){
                word = w;
            }

            if(end - start > max)
                max = end - start;
        }
    }
    std::cout << word << " " << max << std::endl;
}
*/