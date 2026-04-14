#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct media_file{
    std::string title;
    unsigned duration;
    std::vector<struct view *> views;
    //bool type;//0 for video, 1 for audio
};

struct view{
    std::string user;
    double start;
    double finish;
};

std::vector<struct media_file *> files;

// Add a video or music title with the given total duration.  Return 1
// or 0 on success or failure, respectively.
int add_media(const char * title, double duration){

    if (duration <= 0.0)
        return 0;

    for (auto& f : files){
        if(f->title == title)
            return 0;
    }

    struct media_file * f = new struct media_file;

    if (!f)
        return 0;

    f->duration = duration;
    f->title = title;
    files.push_back(f);

    return 1;

}

/*
// Add a media viewing of the given title by the given user of a
// segment defined by the given start and finish times.  Return 1 or 0
// on success or failure, respectively.
*/
int add_view(const char * title, const char * user, double start, double finish){


    for (auto& f : files){

        if(f->title == title){

            if(start >= 0 && finish > start && f->duration >= finish){

                struct view * view = new struct view;

                if (!view)
                    return 0;

                view->user = user;
                view->start = start;
                view->finish = finish;
                f->views.push_back(view);

                return 1;
            }

        }
    }

    return 0;

}

// Clear all media titles and therefore all views.
void clear_media(){

    for (auto f : files){
        for (auto v :f->views){
            delete(v);
        }
        f->views.clear();
        delete(f);
    }
    files.clear();

}

// Clear all media views but keep the media titles.
void clear_views(){

    for (auto f : files){
        for (auto v :f->views){
            delete(v);
        }
        f->views.clear();
    }

}

// Number of unique users who have viewed any portion of the given
// media. Return -1 if the title does not exist.
int unique_viewers(const char * title){

    bool found = false;


    std::vector<std::string> checked_usr;
    //std::set<std::string> checked_usr;

    for (auto& f : files){

        if (f->title == title){

            found = true;

            for(auto& v : f->views){

                //count++;

                
                if(std::find (checked_usr.begin(), checked_usr.end(), v->user) == checked_usr.end()){
                    checked_usr.push_back(v->user);

                }
                

            }
            if(found == true)
                return static_cast<int>(checked_usr.size());
        }

    }
    return -1;
}

// Total time of the given title that the given user has seen at least
// once. Return -1 if the title does not exist.  Return 0 if the user
// does not exist.
double total_time_viewed(const char * title, const char * user){

    double total = 0.0;
    bool found = false;

    for (auto& f : files){

        if (f->title == title){

            for(auto& v : f->views){
                
                if (v->user == user){
                    found = true;
                    total += v->finish - v->start;
                }
            }
            return total;
        }
    }
    
    if (found == false)
        return 0.0;
    return -1.0;
}

// Number of users who viewed the entire duration of the given media
// file in one or more viewings. Return -1 if the title does not exist.
int complete_views(const char * title){

    int n_users = 0;

    bool found = false;

    std::vector<std::string> checked_usr;


    for (auto& f : files){

        if (f->title == title){

            found = true;

            for(auto& v : f->views){

                double time = v->finish - v->start;

                if (time >= f->duration){

                    if(std::find (checked_usr.begin(), checked_usr.end(), v->user) == checked_usr.end()){

                        n_users++;
                        checked_usr.push_back(v->user);

                    }
                }
            }
        }

        if(found == true)
            return n_users;
    }

    return -1;
}


