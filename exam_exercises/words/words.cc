#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "words.h"


struct lines{
    std::vector<std::pair <int, std::string>> array;
    int next_id;
};


struct lines * lines_create(){
    struct lines * l = new struct lines;
    l->next_id = 0;
    return l;
}

void lines_destroy (struct lines * l){

    l->array.clear();
    delete(l);
}

/*
add_line(l,line) adds the given line of text to the given object l. Returns a unique identifier for
that line, or a negative number if memory allocation fails. Notice that the given line object belongs
to the caller, and therefore its content might change. add_line(l,line) must therefore copy that
text in an internally managed data structure.
*/
int add_line (struct lines * l, const char * line){
    std::pair <int, std::string> obj;
    obj.first = l->next_id++;
    obj.second = line;
    l->array.push_back(obj);
    return obj.first;
}

/*
remove_line(l,id) removes the line with the given id from object l. Returns true when the given
id is present and then removed, or false when the given id does not exist.
*/
int remove_line (struct lines * l, int id){

    for(auto it = l->array.begin(); it != l->array.end();){

        if((*it).first == id){
            it = l->array.erase(it);
            //delete((*it));//no delete, delete is only for objects created with null
            return true;
        }
        else it++;

    }
    return false;

}

int match (struct lines * l, const char * output[], int max_output, const char * words){

    std::istringstream input(words);
    std::vector<std::string> W;
    std::string word;

    int count = 0;

    while(input >> word){
        W.push_back(word);
    }

    if (W.size() == 0) 
        return 0;

    for(auto& ln : l->array){

        long unsigned int c = 0;

        for(long unsigned int i = 0; i < W.size(); i++){

            if(ln.second.find(W[i]) != std::string::npos)
                c++;
            else break;
        }

        if (c == W.size() && count < max_output){
            output[count++] = ln.second.c_str();
        }
    }
    //std::cout << count << std::endl;
    return count;
}