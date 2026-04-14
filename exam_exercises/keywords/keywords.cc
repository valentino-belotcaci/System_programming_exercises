#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <cstdlib>

bool sortByVal(const std::pair<std::string, int> &a,
               const std::pair<std::string, int> &b){
    if (a.second == b.second)
        return a.first < b.first; // Lexicographical ascending (ASCII order)
    return (a.second > b.second); // Descending order of frequency
}

bool sortByValRev(const std::pair<std::string, int> &a,
                  const std::pair<std::string, int> &b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return (a.second < b.second); // ascending order of frequency
}


void process_file(unsigned l, unsigned h, int fancy, int revert, FILE * f, const char * filename){

    std::map<std::string, int> words;
    std::string word;

    int num_words = 0;

    //fill the map with the words and their count;

    char line[2001];
    int state = 0;

    while (fgets(line, sizeof(line), f)) {

        char *start = line;
        char *end = line;

        while (*end != 0) {

            unsigned char c = (unsigned char)*end;

            if (isalpha(c)) {

                if (state == 0) {
                    state = 1; 
                    start = end; 
                }

                end++;

            } else {
                if (state == 1) {
                    std::string w(start, end); // copia sicura
                    words[w]++;
                    state = 0;
                }
                end++;
            }
        }
        if (state == 1) { // parola spezzata a fine riga
            std::string w(start, end);
            words[w]++;
            state = 0;
        }
    }

    
    // find the total number of words in the file
    for (const auto &pair : words){
        num_words += pair.second;
    }

    //sort
    std::vector<std::pair<std::string, int>> sorted_words(words.begin(), words.end()); // constructor of a vector

    if(revert == 0)
        std::sort(sorted_words.begin(), sorted_words.end(), sortByVal);
    else
        std::sort(sorted_words.begin(), sorted_words.end(), sortByValRev);


    //print

    if(strcmp(filename, "stdin") != 0)
        std::cout << filename;

    for (const auto &pair : sorted_words) {
        int frequency = pair.second * 100 / num_words;
        if (frequency >= l && frequency <= h) {
            if (fancy == 0)
                std::cout << " " << pair.first;
            else
                std::cout << " " << pair.second << ":" << pair.first;
        }
    }
    std::cout << std::endl;
}


int main(int argc, char *argv[]) {
    unsigned low = 10;
    unsigned high = 90;
    int fancy = 0;
    int reversed = 0;

    int only_files = 0;
    int file_found = 0;

    for (int i = 1; i < argc; ++i) {
        if (only_files) {
            FILE *input = fopen(argv[i], "r");
            if (input == NULL) {
                fprintf(stderr, "Error opening file: %s\n", argv[i]);
                continue;
            }
            file_found = 1;
            process_file(low, high, fancy, reversed, input, argv[i]);
            fclose(input);
        }
        else if (strncmp(argv[i], "low=", 4) == 0) {
            low = (unsigned)atoi(argv[i] + 4);
        }
        else if (strncmp(argv[i], "high=", 5) == 0) {
            high = (unsigned)atoi(argv[i] + 5);
        }
        else if (strcmp(argv[i], "-f") == 0) {
            fancy = 1;
        }
        else if (strcmp(argv[i], "-r") == 0) {
            reversed = 1;
        }
        else if (strcmp(argv[i], "--") == 0) {
            only_files = 1;
        }
        else {
            FILE *input = fopen(argv[i], "r");
            if (input == NULL) {
                fprintf(stderr, "Error opening file: %s\n", argv[i]);
                continue;
            }
            file_found = 1;
            process_file(low, high, fancy, reversed, input, argv[i]);
            fclose(input);
        }
    }

    // If no file was processed, use stdin
    if (!file_found) {
        process_file(low, high, fancy, reversed, stdin, "stdin");
    }

    return 0;
}
