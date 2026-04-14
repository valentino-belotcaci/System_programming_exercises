#include <iostream>
#include <vector>
#include <algorithm>

struct trade{
    double time;
    //float initial_date;
    std::string symbol;
    double quantity;
    double price;
};

struct trades_log{
    std::vector<struct trade *> trades;
    double time_window;
};

/*
A log l can also be explicitly cleared with
clear(l).
*/
void clear(struct trades_log * l){
    for(auto t : l->trades){
        delete(t);
    }
    l->trades.clear();
    l->time_window = 60;
}

struct trades_log * new_log(){

    struct trades_log * l = new struct trades_log;
    l->time_window = 60;
    return l;

}		/* constructor */

void delete_log(struct trades_log * l){

    for(auto t : l->trades){
        delete(t);
    }
    l->trades.clear();
    delete(l);

}	/* destructor */


/*
The library must implement a log of the trades made within a certain time window. The time
window is 60 seconds by default, and can be set for a log l with set_time_window(l,w). When
set_time_window(l,w) reduces the window size compared to the previous value, all the trades
that fall out of the new window must be removed.
*/
void set_time_window(struct trades_log * l, double w){

    double tmax = 0;
    if(l->trades.size() > 0)
        tmax = l->trades[l->trades.size() - 1]->time;

    if(l->time_window > w)
        for(auto it = l->trades.begin(); it != l->trades.end(); ){

            if((*it)->time < tmax - w){
                delete((*it));
                it = l->trades.erase(it);
            }
            else ++it;

        }
    l->time_window = w;
}

/*
A new trade made at time t for quantity q of stock s at price p can be added to a log l with
new_trade(l,t,s,p,q). new_trade must check the validity of the trade, meanining that quantity
and price are positive quantities, and that the time is not less than the time of any of the previous
trades. new_trade which must return 1 on success and 0 on failure or with invalid input.

Notice that adding a new trade at time t for a log with time-window w must result in the effective
removal of all the trades made before time t − w.
*/
int new_trade(struct trades_log * l, double time, const char * symbol, double price, unsigned int quantity){

    if(quantity <= 0 || price <= 0)
        return 0;

    for(auto& t : l->trades){
        if(time < t->time)
            return 0;
    }

    for(auto it = l->trades.begin(); it != l->trades.end(); ){

            if ( (*it)->time < time - l->time_window ) {
                delete *it;                // prima libera la memoria
                it = l->trades.erase(it);  // erase ritorna il prossimo iteratore valido
            } else {
                ++it;                      // incrementi solo quando NON cancelli
            }

        }

    struct trade * new_trade = new trade;
    new_trade->price = price;
    new_trade->quantity = quantity;
    new_trade->symbol = symbol;
    new_trade->time = time;

    l->trades.push_back(new_trade);
    return 1;

}


/*
The library then implements a number of computations over a trade log: total_quantity(l)
returns the total quantity of stocks traded within the time window of a log l; 
*/


unsigned int total_quantity(const struct trades_log * l){

    if(l->trades.size() == 0)   
        return 0;

    unsigned int tot_q = 0;

    for(auto& t : l->trades){
        tot_q += t->quantity;
        
    }

    return tot_q;
}

/*
low_price(l)
and high_price(l) return the lowest and highest price across all stocks, respectively
*/

double high_price(const struct trades_log * l){

    if(l->trades.size() == 0)   
        return 0;

    double max = 0;

    for(auto& t : l->trades){
        if(t->price > max)
            max = t->price;
    }
    return max;
}

double low_price(const struct trades_log * l){

    if(l->trades.size() == 0)   
        return 0;

    double min = l->trades[0]->price;

    for(auto& t : l->trades){
        if(t->price < min)
            min = t->price;
    }

    return min;
}

/*
then
stock_high_price(l,s), stock_low_price(l,s), and stock_avg_price(l,s) return the high,
low, and average price for a given stock s (symbol). 
*/

double stock_high_price(const struct trades_log * l, const char * symbol){

    double max = 0;

    for(auto& t : l->trades)
        if(t->symbol == symbol)
            if(t->price > max)
                max = t->price;


    return max;

}

double stock_low_price(const struct trades_log * l, const char * symbol){

    double min = 99999999;
    int found = 0;

    for(auto& t : l->trades)
        if(t->symbol == symbol){

            found = 1;

            if(t->price < min)
                min = t->price;
        }
    
    if (found == 0)
        return 0;

    return min;
}

double stock_avg_price(const struct trades_log * l, const char * symbol){
    
    double sum = 0;
    double tot = 0;

    for(auto& t : l->trades)
        if(t->symbol == symbol){
            sum += t->price;
            tot++;
        }

    if(tot == 0)
        return 0;

    return sum / tot;

}