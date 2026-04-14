#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

bool sortAlphabetically(const std::pair<std::string, int> &a,
                        const std::pair<std::string, int> &b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
                        }


int main(){
    std::string line;
    std::map<std::string, int> freq;

    while (getline(std::cin, line)){
        int state = 0;
        auto start = line.begin();
        auto end = line. begin();

        while(end != line.end()){
            unsigned char c = (unsigned char) *end;

            if (state == 0 && isalpha(c)){
                state = 1;
                start = end;
            }
            else if (state == 1 && !isalpha(c)){
                std::string w(start,end);
                freq[w]++;
                state = 0;
            }
            end++;
        }
        if(state == 1){
            std::string w(start,end);
            freq[w]++;
        }
    }
    for(auto& pair : freq){
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::vector<std::pair<std::string, int>> vec (freq.begin(), freq.end());

    std::sort(vec.begin(), vec.end(), sortAlphabetically);

    std::cout << std::endl;
    for(auto& pair : vec){
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}