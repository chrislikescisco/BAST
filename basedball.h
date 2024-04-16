#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
// Created by Christian Niebauer on 4/16/2024.
//
#ifndef BAST_BASEDBALLL_H
#define BAST_BASEDBALLL_H

#endif //BAST_BASEDBALLL_H

class Basedball { // I am thinking UpperCamelCase classes, lowerCamelCase funcs,
    class Player {// lower_snake_case variables
    public:
        string player_id;
        string first_name;
        string last_name;
        string position;
        char bats;
        char throws;
        Player();

    };
    class Pitcher : public Player { // yeah, we're using inheritance. so sorry :(
        int wins;
        int losses;
        int games;
        int games_started;
        int complete_games;
        int shutouts;
        int saves;
        int ip_outs;
        int hits_given;
        int home_runs;
        int strike_outs;
        int batted_balls;
        int ba_opp;
        double era;
        int intentional_walks;
        int wild_pitches;
        int hit_by_pitch;
        int balks;
        int batters_facing_pitcher;
        int games_finished;
        int runs_given;
        int sac_bunts;
        int sac_flies;
        // there's one more stat for pitchers: GIDP, but this has a super low
        // sample size and is honestly not even specific to pitchers, fielding
        // also factors into it so i chose not to include it.
    };

    class infielder : public Player {

    };
    Basedball();

};