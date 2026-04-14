#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "videos.h"


struct video{
    char title[101];
    unsigned duration;
    unsigned view_minutes;
    unsigned full_views;
    unsigned id;
    struct video * next;
};


struct platform{
    struct video * head;
    unsigned next_id;
};


struct platform * create (){

    struct platform * p = malloc(sizeof(struct platform));

    if(!p)
        return NULL;
    
    p->head = NULL;
    p->next_id = 0;

    return p;

}   

void destroy (struct platform * p){

    clear(p);
    free(p);

}

void clear (struct platform * p){

    struct video * v = p->head;

    while(v != NULL){
        struct video * tmp = v;
        v = v->next;
        free(tmp);
    }

    p->head = NULL;
    p->next_id = 0;

}



int add_video (struct platform * p, const char * title, int minutes){
    struct video * new_video = malloc(sizeof(struct video));

    if (!new_video)
        return -1;

    new_video->duration = minutes;
    new_video->full_views = 0;
    new_video->view_minutes = 0;
    new_video->id = p->next_id;
    strcpy(new_video->title, title);

    new_video->next = p->head;
    p->head = new_video;

    p->next_id++;

    return new_video->id;
}

int add_view (struct platform * p, int video_id, int minutes){

    for (struct video * v = p->head; v != NULL; v = v->next){

        if(v->id == video_id){

            v->view_minutes += minutes;

            if(minutes >= v->duration)
                v->full_views++;

            return 1;
        }

    }
    return 0;

}

int total_view_minutes (struct platform * p){

    int tot = 0;

    for (struct video * v = p->head; v != NULL; v = v->next){

        tot += v->view_minutes;

    }

    return tot;
}

int total_full_views (struct platform * p){

    int tot = 0;

    for (struct video * v = p->head; v != NULL; v = v->next){

        tot += v->full_views;

    }

    return tot;
}

/*
The video_by_title function takes a title and returns
the identifier of any video with that title, or −1 if no such title exists.
*/

int video_by_title (struct platform * p, const char * title){
    
    for (struct video * v = p->head; v != NULL; v = v->next){

        if(strcmp(v->title, title) == 0)
            return v->id;

    }

    return -1;

}