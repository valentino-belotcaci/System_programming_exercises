#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 5

struct car{
    char maker[21];
    char model_name[21];
    unsigned int engine_power;
    unsigned int price;
};

struct da{
    struct car * car;
    unsigned size;
    unsigned allocated_size;
};

struct da * da_create(){
    struct da * a = malloc(sizeof(struct da));
    if(a){
        a->size = 0;
        a->car = NULL;
        a->allocated_size = 0;
    }
    return a;
}


void da_destroy(struct da * a){
    /*assume that a is a valid pointer to struct da*/
    if(a){
        if(a->car)
            free(a->car);
        free(a);
    }
}

int da_append(struct da * a, struct car * car){
    if(a->allocated_size == a->size){
        /*
        1.allocate new storage
        2. copy all a->size objects from current storage to new storage
        3. free current storage 
        4. use new storage as current storage
        */
        //resizing magic
        size_t new_size =(a->allocated_size) ? 2 * a->allocated_size: INIT_SIZE;

        struct car *new_c = malloc(sizeof(struct car)*new_size);

        if (!new_c)
            return 0;

        if (a->car) {
            //for (size_t i = 0; i < a->size; ++i)
            //    new_A[i] = a->A[i];
            //or we use memcpy  
            memcpy(new_c, a->car, sizeof(struct car) * a->size);
            free(a->car);
        }
        a->car = new_c;
        a->allocated_size = new_size;
    }
    a->car[a->size] = *car;
    a->size++;
    return 1;
}   


int add_from_stdin(struct da *a) {
    if (!a)
        return 0;

    int flag = 1;

    while (1) {
        
        struct car *new_c = malloc(sizeof(struct car));
        if (!new_c) 
            return 0;

        
        int results = scanf("%20s %20s %u %u", 
                            new_c->maker, 
                            new_c->model_name,
                            &new_c->engine_power,
                            &new_c->price);

        if (results != 4) {
            free(new_c);
            break;
        }

        if (da_append(a, new_c) != 1) {
            free(new_c);
            flag = 0;
            break;
        }
        free(new_c);
    }

    return flag;
}


int compare_maker_asc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return strcmp(car1->maker, car2->maker);
}

int compare_maker_desc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return strcmp(car2->maker, car1->maker);
}

int compare_model_asc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return strcmp(car1->model_name, car2->model_name);
}

int compare_model_desc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return strcmp(car2->model_name, car1->model_name);
}

int compare_engine_asc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return car1->engine_power - car2->engine_power;
}

int compare_engine_desc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return car2->engine_power - car1->engine_power;
}

int compare_price_asc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return car1->price - car2->price;
}

int compare_price_desc(const void *a, const void *b) {
    const struct car *car1 = (struct car *)a;
    const struct car *car2 = (struct car *)b;
    
    return car2->price - car1->price;
}


int main(int argc, char * argv[]){

    struct da * a = da_create();

    if(add_from_stdin(a) == 1)
        if (argc == 2){
            if (strcmp(argv[1], "-model") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_model_desc);
            else if (strcmp(argv[1], "+model") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_model_asc);
            else if (strcmp(argv[1], "-maker") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_maker_desc);
            else if (strcmp(argv[1], "+maker") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_maker_asc);
            else if (strcmp(argv[1], "-price") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_price_desc);
            else if (strcmp(argv[1], "+price") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_price_asc);
            else if (strcmp(argv[1], "-power") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_engine_desc);
            else if (strcmp(argv[1], "+power") == 0)
                qsort(a->car, a->size, sizeof(struct car), compare_engine_asc);
        }
        else
            qsort(a->car, a->size, sizeof(struct car), compare_model_desc);
    
    for (int i = 0; i < a->size; i++)
        printf("%s %s %u %u\n", a->car[i].maker, a->car[i].model_name, a->car[i].engine_power, a->car[i].price);

    da_destroy(a);
}