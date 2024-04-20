#include <iostream>
#include <iomanip>
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
        string bats;
        string throws;
        Player();
        Player(string player_id_, string first_name_, string last_name_, string bats_, string throws_);
        struct Stats {
            int games;
            // Hitting stats:
            int at_bats;
            int runs;
            int hits;
            int doubles;
            int triples;
            int home_runs;
            int rbi;
            int stolen_bases;
            int caught_stealing;
            int walks;
            int strikeouts;
            int intentional_walks;
            int hit_by_pitch;
            int sac_bunts;
            int sac_flies;
            int groundouts;
            double batting_avg; // not included in dataset but can be calculated
            double slugging;
            double obp;
            double ops;

            // Fielding stats:
            // Moved to main player class because all players have these
            int games_started;
            int inning_outs;
            int putouts;
            int assists;
            int errors;
            int double_plays;
            int passed_balls;
            int stolen_bases_allowed;
            int caught_stealing_inf;
            int zone_rating;
            Stats();
            void print();
        };
        map<int, Stats> seasons;
        void print(int year);
    };
    class Pitcher : public Player { // yeah, we're using inheritance. so sorry :(
        Pitcher();
        int wins;
        int losses;
        int games;
        int games_started;
        int complete_games;
        int shutouts;
        int saves;
        int ip_outs;
        int hits_allowed;
        int hr_allowed;
        int so_issued;
        int bb_allowed;
        int ba_opp;
        double era;
        int iw_issued;
        int wild_pitches;
        int hbp_issued;
        int balks;
        int batters_facing_pitcher;
        int games_finished;
        int runs_given;
        int sh_issued;
        int sf_issued;
        // there's one more stat for pitchers: GIDP, but this has a super low
        // sample size and is honestly not even specific to pitchers, fielding
        // also factors into it so i chose not to include it.
    };

    class DefaultLT{
        bool operator()(Player player1, Player player2);
    };
public:
    Basedball();
    // we will include all players in a container of some kind, either an array
    // or a set. the array would allow us to sort in-place with heapsort but we
    // would have to iterate through it to search for playerIDs when adding stats
    // from different CSVs (mainly an issue with pitching).
    vector<Player> player_vect; // This is a temporary structure for debugging purposes
    void read();
};