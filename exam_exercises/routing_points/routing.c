#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct point{
    double x;
    double y;
    char name[20];
    struct point * next;
};

struct point * points = NULL;

/* clear the database of points and deallocate all objects within the
library */
void routing_clear(){
    struct point * p = points;

    while (p != NULL) {
        struct point * tmp = p;
        p = p->next;
        free(tmp);
    }

    points = NULL;
}

/* defines or changes the coordinates of a point */
int routing_set_point(const char * name, double x, double y){
    struct point * p = points;

    while (p != NULL){

        if (strcmp(p->name, name) == 0){
            p->x = x;
            p->y = y;
            return 1;
        }

        p = p->next;
    }

    struct point * new_p = malloc(sizeof(struct point));

    if (new_p != NULL){
        strcpy(new_p->name, name);
        new_p->x = x;
        new_p->y = y;
        new_p->next = points;
        points = new_p;
    }
    else return 0;

    return 1;
}

static struct point * find_point(const char * name, const char * name_end) {
    struct point * p = points;
    while (p && !string_equal(p->name, name, name_end))
	p = p->next;
    return p;
}

static double point_distance(const struct point * a, const struct point * b) {
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return sqrt(dx*dx + dy*dy);
}


/* compute the total distance traveled in the given path. A path is a
comma-separated list of point names. The result must be -1 if any
one of the points is undefined. */
double routing_total_distance(const char * sequence) {
    const const char * name;
    const const char * name_end;

    double distance = 0;

    const char * p = sequence;
    const struct point * prev = 0;
    while (*p) {
	    name = p;

        while (*p != ',' && *p != '\0')
            ++p;

        name_end = p;

        const struct point * current = find_point(name, name_end);

        if (!current)
            return -1;

        if (prev) 
            distance += point_distance(current, prev);

        prev = current;
        while (*p == ',')
            ++p;
    }
    return distance;
}
/*
double routing_total_distance(const char * path){


    char * path_copy = strdup(path);  // strdup alloca e copia la stringa
    if (path_copy == NULL) return -1;

    char * token = strtok(path_copy, ",");
    struct point * prev = NULL;
    double total_dist = 0;

    while (token != NULL) {
        struct point * curr = points;
        while (curr != NULL && strcmp(curr->name, token) != 0)
            curr = curr->next;

        if (curr == NULL) {
            free(path_copy);
            return -1;
        }

        if (prev != NULL) {
            double dx = curr->x - prev->x;
            double dy = curr->y - prev->y;
            total_dist += sqrt(dx * dx + dy * dy);
        }

        prev = curr;
        token = strtok(NULL, ",");
    }

    free(path_copy);
    return total_dist;
}*/