#include <iostream>
#include <cctype>
#include <vector>
#include <map>
#include <algorithm>

struct word_gain {
    std::string word;
    int gain;
};

static bool sortByGain(const word_gain & a, const word_gain & b){
    if(a.gain == b.gain)
        return a.word < b.word;
    return a.gain > b.gain;
}

int main(){

    std::map<std::string, int> words;
    std::vector<word_gain> gains;
    int state = 0;

    std::vector<std::string> lines;
    std::string line;

    while (getline(std::cin, line)){
        line += '\n';
        auto start = line.begin();
        auto end = line.begin();

        while (end != line.end()){
            unsigned char c = (unsigned char) * end;

            if (isalpha(c)){
                if (state == 0){
                    state = 1;
                    start = end;
                }
                end++;

            }
            else {
                if(state == 1){
                    std::string w(start, end);
                    words[w]++;
                    state = 0;
                }
                end++;

            }
        }
        if (state == 1){
            std::string w(start, end);
            words[w]++;
            state = 0;
        }
        lines.push_back(line);
    }

    for (auto & pair : words){
            struct word_gain g;
            g.word = pair.first;
            g.gain = pair.first.size() * pair.second - pair.first.size() - 1 - pair.second;
            if (g.gain > 0)
                gains.push_back(g);
    }

    std::sort(gains.begin(), gains.end(), sortByGain);

    if (gains.size() > 128) //asked chat
        gains.resize(128);


    int byte = 128;

    for (auto& gain : gains){
        std::cout << (unsigned char)byte << gain.word;
        //std::cout << byte << std::endl;
        byte++;
    }

    if(!gains.empty())
        std::cout << std::endl;



    for(auto& l : lines){

        auto start = l.begin();        
        auto end = l.begin();
        state = 0;

        while (end != l.end()){
            unsigned char c = (unsigned char) * end;

            if (isalpha(c)){
                if (state == 0){
                    state = 1;
                    start = end;
                }
                end++;

            }
            else {
                if(state == 1){
                    std::string w(start, end);
                    int dis = -1;

                    for(size_t i = 0; i < gains.size(); ++i){
                        if(gains[i].word == w){
                            dis = i + 128;
                            //std::cout << dis << std::endl;
                            putchar((unsigned char)dis);
                            break;
                        }
                    }
                    if(dis == -1) 
                        std::cout << w;
                    state = 0;
                }
                std::cout << (*end);
                end++;

            }
        }
        if (state == 1){
            std::string w(start, end);
            int dis = -1;

            for(size_t i = 0; i < gains.size(); ++i){
                if(gains[i].word == w){
                    dis = i + 129;
                    putchar((unsigned char)dis);
                    break;
                }
            }
            if(dis == -1) 
                std::cout << w;
            state = 0;
        }
    }

}