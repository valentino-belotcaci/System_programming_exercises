#include <iostream>
#include <map>
#include <cctype>
#include <vector>
#include <algorithm>

std::vector<std::pair<std::string, std::string>> rules;

void read_rules(FILE * f){

    std::pair<std::string, std::string> rule;

    char line [2001];
    int state = 0;

    std::string text;

    while (fgets(line, sizeof(line), f)) {
        char * start = line;
        char * end = line;

        while (*end != 0){
            unsigned char c = (unsigned char) *end;

            if (state == 0 && c != ':'){
                end++;
            }
            else if (state == 0 && c == ':'){
                state = 1;
                std::string pattern(start, end);
                rule.first = pattern;
                end++;
                start = end;
            }else if (state == 1 && c != '\n'){
                state = 1;
                end++;
            }
            else if (state == 1 && c == '\n'){
                end++;
                std::string t(start, end - 1);
                text += t;
                //std::cout << std::endl << "aaaa = " << text << std::endl;
                state = 2;
            }
            else if (state == 2 && c == ':'){
                text += '\n';
                state = 1;
                end++;
                start = end;
            }
            else if (state == 2 && c != ':'){
                rule.second = text;
                text.clear();
                //std::cout<< "bbbb" << rule.second;
                rules.push_back(rule);
                state = 0;
                end++;
            }
        }
    }
    if (state == 2) {
            rule.second = text;
            rules.push_back(rule);
        }

    //for (auto & pair : rules)
    //    std::cout << pair.first << "--->" << pair.second << std::endl;

}

void process_stdin(){
    char line [2001];

    while (fgets(line, sizeof(line), stdin)) {
    std::string s(line);  // ← fix

    for (size_t i = 0; i < s.size(); ) {
        bool matched = false;

        for (auto& rule : rules) {
            if (s.compare(i, rule.first.size(), rule.first) == 0) {
                std::cout << rule.second;
                i += rule.first.size();
                matched = true;
                break;
            }
        }

        if (!matched) {
            std::cout << s[i];
            ++i;
        }
    }
}

}




int main(int argc, char * argv[]){



    if (argc > 1){
        for (int i = 1; i < argc; ++i) {

            FILE *input = fopen(argv[i], "r");

            if (input == NULL) {
                fprintf(stderr, "invalid rules file %s\n", argv[i]);
                continue;
            }

            read_rules(input);
            process_stdin();

            fclose(input);
        }
    }

    // If no file was processed, use file RULES
    else{

        FILE *input = fopen("RULES", "r");

        if (input == NULL) {
            fprintf(stderr, "invalid rules file %s\n", "RULES");
            return EXIT_FAILURE;
        }

        read_rules(input);
        process_stdin();


        fclose(input);
    }
}
