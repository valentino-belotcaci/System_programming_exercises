#include <vector>
#include <algorithm>
#include <iostream>
#include <map>


int main(){
    std::string pattern;

    std::getline(std::cin, pattern);

    std::string line;

    if (pattern.empty())
        return EXIT_SUCCESS;


    while(std::getline(std::cin, line)){
        int pos = 0;
        for(int pos = line.find(pattern, 0); pos != std::string::npos; pos = line.find(pattern, pos + 1)){
            std::cout << pos << " ";
        }
    }
}