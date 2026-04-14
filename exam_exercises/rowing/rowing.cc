#include <iostream>
#include <vector>
#include <algorithm>
#include "rowing.h"

struct person{
    std::string name;
    bool assigned;
    int km;
    int excursions;
};


struct boat{
    std::string name;
    unsigned int km;
    unsigned int crew_size;
    bool assigned;
    int excursions;
};

struct club{
    std::vector<struct boat * > boats;
    std::vector<struct person *> members;
};

struct excursion{
    struct boat * boat;
    struct club * club;
    std::vector<struct person *> crew;
};



struct club * create_club (){
    struct club * c = new struct club;
    return c;
}
void destroy_club (struct club * c){
    delete c;
}

/*
add_boat(c,name,max_crew) adds a boat with the given name and maximum crew size to club
c. Within a club, boats are uniquely identified by name. A boat with a maximum crew of four can
take between one and four persons on an excursion. Return 1 on success. Return 0 on error or if
resources are exhausted. It is an error to add two boats with the same name in the same club. It is
also an error to have a maximum crew size less than 1.
*/
int add_boat (struct club * c, const char * name, unsigned int max_crew){

    if (max_crew < 1)
        return 0;

    for(auto& boat : c->boats){

        if(boat->name == name)
            return 0;

    }
    
    struct boat * b = new struct boat;

    b->crew_size = max_crew;
    b->name = name;
    b->assigned = 0;
    b->excursions = 0;
    b->km = 0;

    c->boats.push_back(b);

    return 1;
}

/*
add_person(c,name) adds a person to club c. Persons are also identified uniquely by name within
a club. It is therefore an error to add two persons with the same name in the same club. Return 1 on success or 0 on error
*/
int add_person (struct club * c, const char * name){

    for (auto& person : c->members){
        if (person->name == name)
            return 0;
    }
    struct person * p = new struct person;
    p->assigned = 0;
    p->excursions = 0;
    p->km = 0;
    p->name = name;
    c->members.push_back(p);
    return 1;

}

/*
create_excursion(c) create an excursion object to prepare an excursion within club c. Return
a valid pointer to a new excursion object. Return the null pointer if memory is exhausted and
therefore the creation of a new excursion object fails.
*/
struct excursion * create_excursion (struct club *c){
    struct excursion * e = new struct excursion;
    e->club = c;
    e->boat = nullptr;
    return e;
}

/*
use_boat(e,name) assigns the named boat to the excursion e. Return 1 on success. In this case,
the boat remains assigned to the excursion until the excursion is closed or canceled. Return 0 if
the boat does not exist or is not available because it is currently assigned to another excursion.
*/
int use_boat (struct excursion *e, const char *name){

    if(e->boat != nullptr)
        return 0;

    for (auto& boat : e->club->boats){

        if (boat->name == name){

            if(boat->assigned == 0){

                boat->assigned = 1;
                e->boat = boat;
                return 1;
            }

        }
    }
    return 0;

}


/*
add_crew(e,name) assigns the named person as a crew member for the excursion e. Return 1
on success. In this case, the person is assigned and remains assigned to the given excursion until
that excursion is canceled or closed. Return 0 if the excursion does not yet have an assigned boat,
or if the maximum crew capacity of the boat has already been reached, or if the named person
does not belong to the club, or if the named person has already been added to the crew of another
excursion.
*/
int add_crew (struct excursion *e, const char *name){

    if(e->boat == nullptr || e->crew.size() == e->boat->crew_size)
        return 0;

    for(auto& person : e->club->members){

        if (person->name == name){

            if(person->assigned == 0){

                person->assigned = 1;
                e->crew.push_back(person);
                return 1;
            }
        }
    }
    return 0;
}

/*
close_excursion(e,k) confirms that the given excursion has ended successfully with the given
distance k traveled (in kilometers). The excursion object e is also destroyed and all its allocated
resources are properly released. Return 1 on success. Return 0 when the given excursion has not
been set up properly, with a valid boat and a crew of at least one person. In this case, the excursion
object remains valid.
*/
int close_excursion (struct excursion *e, unsigned int k){

    if (e->boat == nullptr || e->crew.size() < 1)
        return 0;

    e->boat->km += k;
    e->boat->excursions++;
    e->boat->assigned = 0;

    for(auto& person : e->crew){
        person->assigned = 0;
        person->excursions++;
        person->km += k;
    }
    delete e;
    return 1;

}

/*
cancel_excursion(e) the given excursion is canceled. 
The excursion object e is properly destroyed; all its allocated resources are released.
*/

void cancel_excursion (struct excursion *e){

    if (e->boat != nullptr)
        e->boat->assigned = 0;

    for(auto& person : e->crew){
        person->assigned = 0;
    }
    delete e;
}

/*
get_crew_excursions(c,name) return the number of excursions made by the given member of
the club. Return −1 in case of error, for example if the given person does not belong to the club.
*/

int get_crew_excursions (struct club * c, const char *name){
    for(auto& member : c->members){
        if (member->name == name)
            return member->excursions;
    }
    return -1;
}

/*
get_crew_kilometers(c,name) return the total number of kilometers 
traveled in completed excursions made by the given member of club c. Return −1 in case of error, for example if the given
person does not belong to the club.
*/
int get_crew_kilometers (struct club * c, const char * name){
    for(auto& member : c->members){
        if (member->name == name)
            return member->km;
    }
    return -1;
}

/*
boat_available(c,name) return 1 if the boat is available, or 0 if it is not available. Return −1 in
case of error, if the given named boat does not exist in club c.
*/

int boat_available (struct club * c, const char * name){
    for(auto& boat : c->boats){
        if(boat->name == name){
            if(boat->assigned == 0)
                return 1;
            else return 0;
        }
    }
    return -1;
}

/*
get_boat_excursions(c,name) return the number of excursions made with the given boat of
club c. Return −1 in case of error, if club c does not have the given boat.
*/

int get_boat_excursions (struct club *c, const char *name){
    for(auto& boat : c->boats){
        if(boat->name == name)
            return boat->excursions;
    }
    return -1;
}

/*
get_boat_kilometers(c,name) return the number of kilometers traveled with the given boat of
club c. Return −1 in case of error, if club c does not have the given boat.
*/

int get_boat_kilometers (struct club *c, const char *name){
    for(auto& boat : c->boats){
        if(boat->name == name)
            return boat->km;
    }
    return -1;
}
