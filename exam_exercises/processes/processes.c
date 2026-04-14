#include <stdio.h>
#include <stdlib.h>
#include "processes.h"


struct processes{
    struct process * head;
};

struct process{
    int pid;
    int ppid;
    char user [9];
    int priority;
    float usage;
    long int rs;
    long int size;
    long int vsize;
    char command [16];
    struct process * next;
};

struct processes * new_processes(){

    struct processes * p = malloc(sizeof(struct processes));

    if (!p)
        return NULL;

    p->head = NULL;

    return p;

}

void clear(struct processes * p){
    struct process * pc = p->head;

    while (pc != NULL) {
        struct process * tmp = pc;
        pc = pc->next;
        free(tmp);
    }

    p->head = NULL;
}

void delete(struct processes * p){

    clear(p);
    free(p);

}

/*
add_from_file(p, filename) reads information on processes from a given input file and returns
0 on error or 1 on success. Each input line contains information about one active process, as in the
following example:
2331 2264 carzanig 19 2.4 317828 378876 3743140 firefox
*/

int add_from_file(struct processes * p, const char * filename){


    FILE * f = fopen(filename, "r");

    if (f == NULL){
        printf("error opening file %s", filename);
        return 0;
    }

    int found_process = 0;

    while (1){

        struct process * new_p = malloc(sizeof(struct process));
        
        if (!new_p){
            fclose(f);
            return 0;
        }

        int read = fscanf(f,"%d%d%8s%d%f%li%li%li%15s", 
        &new_p->pid,
        &new_p->ppid,
        new_p->user,
        &new_p->priority,
        &new_p->usage,
        &new_p->rs,
        &new_p->size,
        &new_p->vsize,
        new_p->command);

        if (read == EOF) {
            free(new_p);
            break;
        }

        if (read != 9) {
            free(new_p);
            continue;
        }

        new_p->next = NULL;

        if (p->head == NULL) {
            // If the list is empty
            p->head = new_p;
        } else {

            struct process *last = p->head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = new_p;  // Link the last node to the new_proc
        }
        found_process++;

        // Add the process to the head of the list

        /*pc->next = p->head;
        p->head = pc;
        num_proc++;*/

    }
    

    fclose(f);

    if (found_process == 0)
        return 0;
    return 1;
}


struct query_result {
    struct query query;
    struct process * result;
};

int matches_field(int proc_val, int query_val){

    if(query_val == 0)
        return 1;
    if(query_val > 0){
        if(query_val == proc_val)
            return 1;
    }else{
        query_val *= -1;
        if(proc_val > query_val)
            return 1;
    }
    return 0;

}



struct query_result * search(struct processes * p, const struct query * q){

    struct process * pc = p->head;

    while (pc != NULL){

        if (matches_field(pc->priority, q->priority) == 1 &&
            matches_field(pc->rs, q->rss) == 1 &&
            matches_field(pc->size, q->size) == 1 &&
            matches_field(pc->vsize, q->vsize) == 1 &&
            matches_field(pc->usage, q->cpu_usage) == 1)
        {

        struct query_result * qr = malloc(sizeof(struct query_result));

        if (!qr)
            return 0;

        qr->query.priority = q->priority;
        qr->query.rss = q->rss;
        qr->query.size = q->size;
        qr->query.vsize = q->vsize;
        qr->query.cpu_usage = q->cpu_usage;
        qr->result = pc;
        return qr;

        }
        pc = pc->next;
    }
    return NULL;
}

int get_pid(struct query_result *r){
    return r->result->pid;
}

int get_ppid(struct query_result *r){
    return r->result->ppid;
}

const char * get_user(struct query_result *r){
    return r->result->user;
}

int get_priority(struct query_result *r){
    return r->result->priority;
}

float get_cpu_usage(struct query_result *r){
    return r->result->usage;
}

long int get_rss(struct query_result *r){
    return r->result->rs;
}

long int get_size(struct query_result *r){
    return r->result->size;
}

long int get_vsize(struct query_result *r){
    return r->result->vsize;
}

const char * get_command(struct query_result *r){
    return r->result->command;
}

void terminate_query(struct query_result * r){
    free(r);
}

struct query_result * next(struct query_result * r) {
    struct process * current = r->result->next;

    while (current != NULL) {
        if (
            matches_field(current->priority, r->query.priority) &&
            matches_field(current->rs, r->query.rss) &&
            matches_field(current->size, r->query.size) &&
            matches_field(current->vsize, r->query.vsize) &&
            (
                r->query.cpu_usage == 0.0f ||
                (r->query.cpu_usage > 0.0f && current->usage == r->query.cpu_usage) ||
                (r->query.cpu_usage < 0.0f && current->usage > -r->query.cpu_usage)
            )
        ) {
            r->result = current;
            return r;
        }

        current = current->next;
    }

    free(r);
    return NULL;
}
