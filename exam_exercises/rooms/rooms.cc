#include "rooms.h"
#include <iostream>
#include <vector>//dynamic array
#include <map>
#include <algorithm>


std::vector<room *> rooms;


struct reservation{
    struct room * r;
    struct schedule * s;
    std::string description;
};

std::vector<reservation *> reservations;

/*
add_rooms(begin,end) adds rooms from an array of room objects. The begin pointer points to
the first room to add, and end points immediately past the last room to add. If a room already
exists, then its capacity must be updated with the given new value. Notice that the room objects
passed to add_rooms() are owned by the application. Their values might change or they might
even be deallocated immediately after the call to add_rooms().
*/
void add_rooms(const room * begin, const room * end){

    for(auto i = begin; i != end; i++){
        bool found = false;
        for (auto& r : rooms){
            if(i->floor == r->floor && i->number == r->number){
                r->capacity = i->capacity;
                found = true;
                break;
            }
        }
        if (found == false){
            struct room * r = new struct room;
            r->capacity = i->capacity;
            r->floor = i->floor;
            r->number = i->number;
            rooms.push_back(r);
        }
    }
}

/*
make_reservation(r, t, description) makes a reservation for a given event. The room object
r and the schedule object s express requirements for the reservation. In particular, r->capacity is
the minimum required capacity of the room. However, if r->capacity is equal to ANY_CAPACITY,
then any capacity would work. Similarly, r->floor requires a specific floor, or no specific floor
if that is equal to ANY_FLOOR, and r->number requires a specific room number, or not if equal to
ANY_ROOM_NUMBER. The schedule object s represents a period of a given duration s->duration
greater than zero that should be scheduled between a given start time s->start and a given
finish time s->finish. A reservation can be made in a room if there is an interval of duration
s->duration between times s->start and s->finish (inclusive) that does not overlap with any
other event scheduled in the same room. Notice that an interval that finishes at time t does not
overlap with another interval that starts at time t.
make_reservation returns 1 or 1 when a room is found or not found, respectively. If a room is
found, make_reservation also sets the values of r->floor, r->number, and r->capacity with
those of the chosen room, and s->start and s->finish with the chosen time interval in which
that room is available. When multiple rooms or schedules are available, make_reservation must
select the lowest compatible room capacity, the lowest floor, the lowest room number, and the
lowest starting time, in this order.
*/

int make_reservation(room * r, schedule * t, const char * event){

    for(auto& room : rooms){
        if((room->capacity >= r->capacity || r->capacity == ANY_CAPACITY)
        && (room->floor == r->floor || r->floor == ANY_FLOOR)
        && (room->number == r->number || r->number == ANY_ROOM_NUMBER)){

            if(t->duration <= 0 || t->start < 0)
                return 0;
            else if (t->finish != t->start + t->duration)
                t->finish = t->start + t->duration;
            

            for(auto& res : reservations){
                if((room->capacity == res->r->capacity)
                && (room->floor == res->r->floor)
                && (room->number == res->r->number)){

                    if (!(res->s->finish <= t->start || res->s->start >= t->finish)) {
                        // overlap found
                        return 0;
                    }
                }

            }

            *r = *room;
            // alloca nuova room
            struct room * real_room = new struct room;
            *real_room = *room;  // copia i dati della stanza trovata

            // alloca nuova schedule
            struct schedule* real_schedule = new struct schedule;
            *real_schedule = *t; // copia i dati coerenti

            // alloca la reservation
            struct reservation * reser = new struct reservation;
            reser->r = real_room;
            reser->s = real_schedule;
            reser->description = event;

            // aggiungi alla lista
            reservations.push_back(reser);
            return 1;

        }
    }
    return 0;

}

/*
cancel_reservation(floor, number, start) cancels an existing reservation. If a reservation
exists for the given room, as identified by floor and number, and for the given start time, then
the result is 1, and that reservation is canceled. Otherwise, the result is 0 and no reservation is
canceled.
*/
int cancel_reservation(int floor, int number, int start){

    for(auto it = reservations.begin(); it != reservations.end(); ++it){

        if((*it)->r->floor == floor &&
            (*it)->r->number == number &&
            (*it)->s->start == start){

                delete((*it)->r);
                delete((*it)->s);
                delete((*it));
                reservations.erase(it);

                return 1;
        }
    }
    return 0;
}


/*
print_schedule(out, floor, number, start, finish) selects rooms and prints their schedule on the given out stream. The floor and room numbers determine which rooms are selected.
These are the rooms with number number or with any room number if number is ANY_NUMBER, on
floor floor or any floor if floor is ANY_FLOOR. The given start and finish times determine
which events are selected. These are all the events in selected rooms that overlap with the given
interval, or more specifically the events that start at or before the given finish time or that end
at or after the given start time.
The output consist of a set of lines for each room. The first line identifies a room with the format “room room-number floor floor-number:”. Each of the following lines describes an event
scheduled in that room with the format “event: start-time finish-time description”. If there are
no events scheduled for that room in the requested interval, then no lines follow. The rooms must
be sorted first by floor and then by room number.
*/

bool sortByRoom(const struct room * a,
               const struct room * b){
    if (a->floor == b->floor)
        return a->number < b->number; // ascending order of floor
    return (a->floor < b->floor); // ascending order of number
}

bool sortByStart(const struct reservation * a,
               const struct reservation * b){
    return (a->s->start < b->s->start); // ascending order of start
}

void print_schedule(std::ostream & output, int floor, int number, int start, int finish){

    std::vector<room *> selected_rooms;

    for(auto& room : rooms){
        if((room->number == number || number == ANY_ROOM_NUMBER) &&
        (room->floor == floor || floor == ANY_FLOOR))
            selected_rooms.push_back(room);
    }

    std::sort(selected_rooms.begin(), selected_rooms.end(), sortByRoom);

    for(auto& room : selected_rooms){

        output << "room" << " " << room->number << " " << "floor" << " " << room->floor << ":" << std::endl;

        std::vector<reservation *> ev;

        for(auto& res : reservations){
            if(res->r == room){
                if(res->s->start <= finish &&
                res->s->finish >= start)
                    ev.push_back(res);
            }
        }
        std::sort(ev.begin(), ev.end(), sortByStart);

        for(auto& e : ev)
            output << "event" << " " << e->s->start << " " << e->s->finish << " " << e->description << std::endl;

    }

}

void clear() {
    for (auto r : rooms) {
        delete r;
    }
    rooms.clear();

    for (auto res : reservations) {
        delete res->r;
        delete res->s;
        delete res;
    }
    reservations.clear();
}