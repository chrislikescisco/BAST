#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
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

            // Pitching stats (map will be empty for non-pitchers so we don't have 20 unused int values attached to 90%
            // of the player objects
            void print();
        };
        struct PStats {
            int wins;
            int losses;
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
            PStats();

            void print();
        };
        map<int, Stats> seasons;
        map<int, PStats> pitching_seasons;
        void print();
    };
    static unordered_set<string> pitchers;
//        int wins;
//        int losses;
//        int games;
//        int games_started;


    // These won't actually work, nothing ever gets assigned to the "stats" object, they're all put in a map<int, Stats>
    // so that stats can be compared by season. I will add parameters for both seasons (and I will add a year 0 into each
    // map which contains combined career stats, as well as a year 1 which contains career averages.)
    class ComparePlayers {
    public:
        virtual bool operator()(const Player &a, const int &yr1, const Player &b, const int& yr2) const = 0;
    };
    class CompareByBattingAvg : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).batting_avg > b.seasons.at(yr2).batting_avg;
        }
    };
    class CompareByHomeRuns : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).home_runs > b.seasons.at(yr2).home_runs;
        }
    };
    class CompareByRBI : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).rbi > b.seasons.at(yr2).rbi;
        }
    };
    class CompareByAtBats : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override{
            return a.seasons.at(yr1).at_bats > b.seasons.at(yr2).at_bats;
        }
    };
    class CompareRuns : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).runs > b.seasons.at(yr2).rbi;
        }
    };
    class CompareHits : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).hits > b.seasons.at(yr2).hits;
        }
    };
    class CompareDoubles : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).doubles > b.seasons.at(yr2).doubles;
        }
    };
    class CompareTriples : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).triples > b.seasons.at(yr2).triples;
        }
    };
    class CompareStolenBases : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).stolen_bases > b.seasons.at(yr2).stolen_bases;
        }
    };
    class CompareStealing : public ComparePlayers {
    public:
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).caught_stealing > b.seasons.at(yr2).caught_stealing;
        }
    };
    class CompareStrikes : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).strikeouts > b.seasons.at(yr2).strikeouts;
        }
    };
    class CompareWalks : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).intentional_walks > b.seasons.at(yr2).intentional_walks;
        }
    };
    class CompareHitPitch : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).hit_by_pitch > b.seasons.at(yr2).hit_by_pitch;
        }
    };
    class CompareSacs : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).sac_bunts > b.seasons.at(yr2).sac_bunts;
        }
    };
    class CompareSacFlies : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).sac_flies > b.seasons.at(yr2).sac_flies;
        }
    };
    class CompareGrounds : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).groundouts > b.seasons.at(yr2).groundouts;
        }
    };
    class CompareSlugging : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).slugging > b.seasons.at(yr2).slugging;
        }
    };
    class CompareObp : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).obp > b.seasons.at(yr2).obp;
        }
    };
    class CompareOps : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).ops > b.seasons.at(yr2).ops;
        }
    };
    class CompareGameStarted : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).games_started > b.seasons.at(yr2).games_started;
        }
    };
    class CompareInOut : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).inning_outs > b.seasons.at(yr2).inning_outs;
        }
    };
    class ComparePutOuts : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).putouts > b.seasons.at(yr2).putouts;
        }
    };
    class CompareAssists : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).assists > b.seasons.at(yr2).assists;
        }
    };
    class CompareErros : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).errors > b.seasons.at(yr2).errors;
        }
    };
    class CompareDoublePlays : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).double_plays > b.seasons.at(yr2).double_plays;
        }
    };
    class ComparePassedBalls : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).passed_balls > b.seasons.at(yr2).passed_balls;
        }
    };
    class ComparedStolenAllowed : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).stolen_bases_allowed > b.seasons.at(yr2).stolen_bases_allowed;
        }
    };
    class ComparedStealingInf : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).caught_stealing_inf > b.seasons.at(yr2).caught_stealing_inf;
        }
    };
    class ComparedZoneRating : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.seasons.at(yr1).zone_rating > b.seasons.at(yr2).zone_rating;
        }
    };
    class ComparedCompleteGames : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).complete_games > b.pitching_seasons.at(yr2).complete_games;
        }
    };
    class ComparedShutouts : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).shutouts > b.pitching_seasons.at(yr2).shutouts;
        }
    };
    class ComparedSaved : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).saves > b.pitching_seasons.at(yr2).saves;
        }
    };
    class ComparedIp : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).ip_outs > b.pitching_seasons.at(yr2).ip_outs;
        }
    };
    class ComparedHitsAll : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).hits_allowed > b.pitching_seasons.at(yr2).hits_allowed;
        }
    };
    class ComparedHrAll : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).hr_allowed > b.pitching_seasons.at(yr2).hr_allowed;
        }
    };
    class ComparedSoIssued : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).so_issued > b.pitching_seasons.at(yr2).so_issued;
        }
    };
    class ComparedBbAll : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).bb_allowed > b.pitching_seasons.at(yr2).bb_allowed;
        }
    };
    class ComparedBaOpp : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).ba_opp > b.pitching_seasons.at(yr2).ba_opp;
        }
    };
    class CompareEra : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).era > b.pitching_seasons.at(yr2).era;
        }
    };
    class CompareIwIssued : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).iw_issued > b.pitching_seasons.at(yr2).iw_issued;
        }
    };
    class CompareWildPitches : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).wild_pitches > b.pitching_seasons.at(yr2).wild_pitches;
        }
    };
    class CompareHbpIssued : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).hbp_issued > b.pitching_seasons.at(yr2).hbp_issued;
        }
    };
    class CompareBalks : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).balks > b.pitching_seasons.at(yr2).balks;
        }
    };
    class CompareBattersvPitcher : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).batters_facing_pitcher > b.pitching_seasons.at(yr2).batters_facing_pitcher;
        }
    };
    class CompareGamesFinished : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).games_finished > b.pitching_seasons.at(yr2).games_finished;
        }
    };
    class CompareRunsGiven : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).runs_given > b.pitching_seasons.at(yr2).runs_given;
        }
    };
    class CompareShIssued : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).sh_issued > b.pitching_seasons.at(yr2).sh_issued;
        }
    };
    class CompareSfIssued : public ComparePlayers {
        bool operator()(const Player& a, const int& yr1, const Player& b, const int& yr2) const override {
            return a.pitching_seasons.at(yr1).sf_issued > b.pitching_seasons.at(yr2).sf_issued;
        }
    };
    class MaxHeap {
    private:
        vector<Player> data; // stores heap elements
        const ComparePlayers* comparator; // points to comparator object
        int year1, year2;
    public:
        MaxHeap(const ComparePlayers& comp, int yr1, int yr2) : comparator(&comp), year1(yr1), year2(yr2) {}
        void addPlayer(const Player& value) {
            data.push_back(value);
            int i = data.size() - 1;
            while (i != 0) {
                int parent = (i - 1) / 2;
                if (!(*comparator)(data[parent], year1, data[i], year2)) {
                    swap(data[i], data[parent]);
                    i = parent;
                } else {
                    break;
                }
            }
        }
        Player extractMax() {
            if (data.empty()) {
                cout << "No players to show yet";
            }
            swap(data[0], data.back());
            Player max = data.back();
            data.pop_back();
            if (!data.empty()) {
                heapifyDown(0);
            }
            return max;
        }
        bool isEmpty() const {
            return data.empty();
        }
        void heapifyDown(int idx) {
            int size = data.size();
            int largest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;

            if (left < size && (*comparator)(data[left], year1, data[largest], year2)) {
                largest = left;
            }
            if (right < size && (*comparator)(data[right], year1, data[largest], year2)) {
                largest = right;
            }

            if (largest != idx) {
                swap(data[idx], data[largest]);
                heapifyDown(largest);
            }
        }
        void heapSort(vector<Player>& players, ComparePlayers& comp, int year1, int year2){
            MaxHeap h(comp, year1, year2);
            for(const Player& player : players) {
                h.addPlayer(player);
            }
            vector<Player> sorted;
            while (!h.isEmpty()) {
                sorted.push_back(h.extractMax());
            }
            reverse(sorted.begin(),sorted.end());
            players = sorted;
        }
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