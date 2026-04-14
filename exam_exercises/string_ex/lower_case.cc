#include <vector>
#include <algorithm>
#include <iostream>
#include <map>


int main(){
    std::string line;
    std::map < std::string, int> words;
    
    while(std::getline(std::cin, line)){
        auto start = line.begin();
        auto end = line.begin();
        int state = 0;

        while (end != line.end()){
            unsigned char c = (unsigned char) * end;

            if (state == 0 && isalpha(c)){
                state = 1;
                start = end;
            }
            else if (state == 1 && !isalpha(c)){
                std::string w (start,end);
                std::string word;
                for(auto& ch : w){
                    word.push_back(std::tolower((unsigned char)ch));
                }
                words[word]++;
                state = 0;

            }
            end++;
        }
        if (state == 1){
            std::string w (start,end);
            std::string word;
            for(auto& ch : w){
                word.push_back(std::tolower((unsigned char)ch));
            }
            words[word]++;
            state = 0;

        }
    }
    for (auto& pair : words){
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}