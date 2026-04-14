#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct team{
    char name[21];
    int score;
    int games_played;
};

int isPresent(char team[21], int nteams, struct team * teams[]){

    for(int i = 0; i < nteams; i++){
        if(teams[i] != NULL && strcmp(team, teams[i]->name) == 0)
            return i;
    }
    return -1;
}

void sort_teams(int nteams, struct team * teams[]){

    for (int i = 0; i < nteams; i++){

        for(int j = i + 1; j < nteams; j++){
            if(teams[i]->score < teams[j]->score){
                struct team * tmp = teams[i];
                teams[i] = teams[j];
                teams[j] = tmp;
            }
            else if(teams[i]->score == teams[j]->score){
                if(strcmp(teams[i]->name, teams[j]->name) > 0){
                    struct team * tmp = teams[i];
                    teams[i] = teams[j];
                    teams[j] = tmp;
                }
            }
        }

    }

}

int main(int argc, char * argv[]){

    int nteams = 10;

    if (argc > 1)
        nteams = atoi(argv[1]);

    char line[101];
    char team1[21];
    char team2[21];
    int score1 = 0;
    int score2 = 0;

    struct team * teams[nteams];

    //printf("%d",teams[1]->games_played);//segmentation fault
    //solve problem -> initialize to null
    for (int i = 0; i < nteams; i++){
        teams[i] = NULL;
    }

    //printf("%d",teams[1]->games_played);

    int teams_added = 0;//never greater than nteams

    while(fgets(line, 101, stdin)){
        
        if (sscanf(line, "%20s%20s%d%d", team1, team2, &score1, &score2) != 4)
            continue;

        int idx1 = isPresent(team1, nteams, teams);
        int idx2 = isPresent(team2, nteams, teams);
        
        if (idx1 == -1){
            if(teams_added < nteams){
                struct team * new_t = malloc(sizeof(struct team));
                if (!new_t)
                    return EXIT_FAILURE;
                new_t->games_played = 0;
                new_t->score = 0;
                strcpy(new_t->name, team1);
                idx1 = teams_added;
                teams[teams_added++] = new_t;
            }
            else return EXIT_FAILURE;
        }

        if (idx2 == -1){
            if(teams_added < nteams){
                struct team * new_t = malloc(sizeof(struct team));
                if (!new_t)
                    return EXIT_FAILURE;
                new_t->games_played = 0;
                new_t->score = 0;
                strcpy(new_t->name, team2);
                idx2 = teams_added;
                teams[teams_added++] = new_t;
            }
            else return EXIT_FAILURE;
        } 

        if (score1 > score2)
            teams[idx1]->score += 3;
        else if (score1 == score2){
            teams[idx1]->score++;
            teams[idx2]->score++;
        }
        else 
            teams[idx2]->score += 3;

        teams[idx1]->games_played++;
        teams[idx2]->games_played++;

    }

    sort_teams(teams_added, teams);

    for (int i = 0; i < teams_added; i++){
        printf("%s ", teams[i]->name);
        printf("%d ", teams[i]->score);
        printf("%d\n", teams[i]->games_played);
    }

    for(int i = 0; i < teams_added; i++)
        free(teams[i]);

    return EXIT_SUCCESS;

}