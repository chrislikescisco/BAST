#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
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
        Stats stats;
        PStats p;
        void print(int year);
    };
//        int wins;
//        int losses;
//        int games;
//        int games_started;

        // there's one more stat for pitchers: GIDP, but this has a super low
        // sample size and is honestly not even specific to pitchers, fielding
        // also factors into it so i chose not to include it.
    class ComparePlayers {
    public:
        virtual bool operator()(const Player& a, const Player& b) const = 0;
    };
    class CompareByBattingAvg : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.batting_avg > b.stats.batting_avg;
        }
    };
    class CompareByHomeRuns : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.home_runs > b.stats.home_runs;
        }
    };
    class CompareByRBI : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.rbi > b.stats.rbi;
        }
    };
    class CompareByAtBats : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override{
            return a.stats.at_bats > b.stats.at_bats;
        }
    };
    class CompareRuns : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.runs > b.stats.rbi;
        }
    };
    class CompareHits : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.hits > b.stats.hits;
        }
    };
    class CompareDoubles : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.doubles > b.stats.doubles;
        }
    };
    class CompareTriples : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.triples > b.stats.triples;
        }
    };
    class CompareStolenBases : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            return a.stats.stolen_bases > b.stats.stolen_bases;
        }
    };
    class CompareStealing : public ComparePlayers {
    public:
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.caught_stealing > b.stats.caught_stealing;
        }
    };
    class CompareStrikes : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.strikeouts > b.stats.strikeouts;
        }
    };
    class CompareWalks : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.intentional_walks > b.stats.intentional_walks;
        }
    };
    class CompareHitPitch : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.hit_by_pitch > b.stats.hit_by_pitch;
        }
    };
    class CompareSacs : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.sac_bunts > b.stats.sac_bunts;
        }
    };
    class CompareSacFlies : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.sac_flies > b.stats.sac_flies;
        }
    };
    class CompareGrounds : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.groundouts > b.stats.groundouts;
        }
    };
    class CompareSlugging : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.slugging > b.stats.slugging;
        }
    };
    class CompareObp : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.obp > b.stats.obp;
        }
    };
    class CompareOps : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.ops > b.stats.ops;
        }
    };
    class CompareGameStarted : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.games_started > b.stats.games_started;
        }
    };
    class CompareInOut : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.inning_outs > b.stats.inning_outs;
        }
    };
    class ComparePutOuts : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.putouts > b.stats.putouts;
        }
    };
    class CompareAssists : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.assists > b.stats.assists;
        }
    };
    class CompareErros : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.errors > b.stats.errors;
        }
    };
    class CompareDoublePlays : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.double_plays > b.stats.double_plays;
        }
    };
    class ComparePassedBalls : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.passed_balls > b.stats.passed_balls;
        }
    };
    class ComparedStolenAllowed : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.stolen_bases_allowed > b.stats.stolen_bases_allowed;
        }
    };
    class ComparedStealingInf : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.caught_stealing_inf > b.stats.caught_stealing_inf;
        }
    };
    class ComparedZoneRating : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.stats.zone_rating > b.stats.zone_rating;
        }
    };
    class ComparedCompleteGames : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.complete_games > b.p.complete_games;
        }
    };
    class ComparedShutouts : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.shutouts > b.p.shutouts;
        }
    };
    class ComparedSaved : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.saves > b.p.saves;
        }
    };
    class ComparedIp : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.ip_outs > b.p.ip_outs;
        }
    };
    class ComparedHitsAll : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.hits_allowed > b.p.hits_allowed;
        }
    };
    class ComparedHrAll : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.hr_allowed > b.p.hr_allowed;
        }
    };
    class ComparedSoIssued : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.so_issued > b.p.so_issued;
        }
    };
    class ComparedBbAll : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.bb_allowed > b.p.bb_allowed;
        }
    };
    class ComparedBaOpp : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.ba_opp > b.p.ba_opp;
        }
    };
    class CompareEra : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.era > b.p.era;
        }
    };
    class CompareIwIssued : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.iw_issued > b.p.iw_issued;
        }
    };
    class CompareWildPitches : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.wild_pitches > b.p.wild_pitches;
        }
    };
    class CompareHbpIssued : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.hbp_issued > b.p.hbp_issued;
        }
    };
    class CompareBalks : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.balks > b.p.balks;
        }
    };
    class CompareBattersvPitcher : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.batters_facing_pitcher > b.p.batters_facing_pitcher;
        }
    };
    class CompareGamesFinished : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.games_finished > b.p.games_finished;
        }
    };
    class CompareRunsGiven : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.runs_given > b.p.runs_given;
        }
    };
    class CompareShIssued : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.sh_issued > b.p.sh_issued;
        }
    };
    class CompareSfIssued : public ComparePlayers {
        bool operator()(const Player& a, const Player& b) const override {
            a.p.sf_issued > b.p.sf_issued;
        }
    };
    class MaxHeap {
    private:
        vector<Player> data;
        const ComparePlayers* comparator; // points to comparator object
    public:
        MaxHeap(const ComparePlayers& comp) : comparator(&comp) {}
        void addPlayer(Player value) {
            data.push_back(value);
            int i = data.size() - 1;
            while (i != 0) {
                int parent = (i - 1) / 2;
                if (!(*comparator)(data[parent], data[i])) {
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

            if (left < size && (*comparator)(data[left], data[largest])) {
                largest = left;
            }
            if (right < size && (*comparator)(data[right], data[largest])) {
                largest = right;
            }

            if (largest != idx) {
                swap(data[idx], data[largest]);
                heapifyDown(largest);
            }
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