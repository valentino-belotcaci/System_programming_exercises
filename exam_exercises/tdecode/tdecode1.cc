#include <iostream>
#include <map>
#include <cctype>




int main(){

    std::map<int, std::string> encode;

    std::string word;
    
    int c = 0;

    int firstByte = getchar();

    if(firstByte == EOF)
        return EXIT_SUCCESS;


    if(firstByte < 128){
        putchar(firstByte);
        while ((c = getchar()) != EOF){
            putchar(c);
        }
    }

    else{
        int c = 0;
        int state = 0;
        int byte = firstByte;

        //char * line[1001];
        
        while((c = getchar()) != '\n' && c != EOF){

            if(c > 127 && state == 0){
                byte = c;
                state = 0;
            }
            else if(c < 128 && (state == 0 || state == 1)){
                state = 1;
                word.push_back(c);
            }
            else if (c > 127 && state == 1){
                state = 0;
                encode[byte] = word;
                word.clear();
                byte = c;
            }
        }

        if (!word.empty())
            encode[byte] = word;

        //for(auto& p : encode){
        //            std::cout << "byte = " << p.first << " word = " << p.second <<std::endl;
        //        }


        while((c = getchar()) != EOF){
            if(c > 127){

                auto found = encode.find(c);

                if (found != encode.end()){
                    std::cout << found->second;
                }
                else return EXIT_FAILURE;
            }
            else
                putchar(c);
        }
    }

        
}




