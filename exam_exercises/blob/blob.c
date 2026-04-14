#include "blob.h"

unsigned int count_char (const struct blob * b, char c){
    struct chunk_list * sentinel = b->sentinel.next;
    int count = 0;

    while(sentinel != &b->sentinel){

        for(int i = 0; i < sentinel->c->length; i++){
            if(sentinel->c->data[i] == c)
                count++;
        }

        sentinel = sentinel->next;
    }
    return count;
}

unsigned int copy_to_buffer (const struct blob * b, char * buf, unsigned int maxlen){
    struct chunk_list * sentinel = b->sentinel.next;
    int copied = 0;

    while (sentinel != &b->sentinel){
        for(int i = 0; i < sentinel->c->length; i++){

            if(copied < maxlen){
                *buf = sentinel->c->data[i];
                buf++;
                copied++;
            }else return maxlen + 1;
            
        }
        sentinel = sentinel->next;
    }
    return copied;
}

unsigned int copy_to_buffer_reverse (const struct blob * b, char * buf, unsigned int maxlen){
    struct chunk_list * sentinel = b->sentinel.prev;
    int copied = 0;

    while (sentinel != &b->sentinel){
        for(int i = sentinel->c->length - 1; i >= 0; i--){

            if(copied < maxlen){
                *buf = sentinel->c->data[i];
                buf++;
                copied++;
            }else return maxlen + 1;
            
        }
        sentinel = sentinel->prev;
    }
    return copied;
}