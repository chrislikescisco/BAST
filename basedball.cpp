#include "basedball.h"
//
// Created by thatp on 4/16/2024.
//

Basedball::Player::Player() = default;

Basedball::Player::Player(string player_id_, string first_name_, string last_name_, string bats_, string throws_) {
    player_id = player_id_;
    first_name = first_name_;
    last_name = last_name_;
    bats = bats_;
    throws = throws_;
}

Basedball::Player::Stats::Stats() {
    games = 0;
    // Hitting stats:
    at_bats = 0;
    runs = 0;
    hits = 0;
    doubles = 0;
    triples = 0;
    home_runs = 0;
    rbi = 0;
    stolen_bases = 0;
    caught_stealing = 0;
    walks = 0;
    strikeouts = 0;
    intentional_walks = 0;
    hit_by_pitch = 0;
    sac_bunts = 0;
    sac_flies = 0;
    groundouts = 0;
    batting_avg = 0; // not included in dataset but can be calculated
    // Fielding stats:
    // Moved to main player class because all players have these
    games_started = 0;
    inning_outs = 0;
    putouts = 0;
    assists = 0;
    errors = 0;
    double_plays = 0;
    passed_balls = 0;
    stolen_bases_allowed = 0;
    caught_stealing_inf = 0;
    zone_rating = 0;
}

void Basedball::Player::print(int year) {
    cout << year << ": " << endl;
    cout << "Player ID: " << player_id << endl << "Name: " << first_name << ' ' << last_name << endl <<"Bats: " << bats
    << endl << "Throws: " << throws << endl;
    seasons[year].print();
}

void Basedball::Player::Stats::print() {
    cout << fixed << setprecision(3) <<"At bats: " << at_bats << endl << "Runs: " << runs << endl << "Hits: " << hits <<
    endl << "Doubles: " << doubles << endl << "Triples: " << triples << endl << "Home Runs: " << home_runs << endl <<
    "RBI: " << rbi << endl << "Stolen Bases: " << stolen_bases << endl << "Caught Stealing: " << endl << "Walks: " <<
    walks << endl << "Strikeouts: " << strikeouts << endl << "Hit By Pitch: " << hit_by_pitch << endl <<
    "Sacrifice Flies: " << sac_flies << endl << "Groundouts: " << groundouts << endl << "Batting Average: " <<
    batting_avg << endl << "Slugging: " << slugging << endl << "OBP: " << obp << endl << "OPS: " << ops << endl <<
    "Games: " << games  << '\n'<< "Games Started: " << games_started << endl << "Inning Outs: "
    << inning_outs << endl << "Putouts: " << putouts << endl << "Assists: " << assists << endl << "Errors: " << errors
    << endl << "Double Plays: " << double_plays << endl << "Passed Balls: " << passed_balls << endl <<
    "Stolen Bases Allowed: " << stolen_bases_allowed << endl << "Caught Stealing (Infielder): " << caught_stealing_inf
    << endl << "Zone Rating: " << zone_rating << endl << endl;
}

Basedball::Pitcher::Pitcher() {
    wins = 0;
    losses = 0;
    games = 0;
    games_started = 0;
    complete_games = 0;
    shutouts = 0;
    saves = 0;
    ip_outs = 0;
    hits_allowed = 0;
    hr_allowed = 0;
    so_issued = 0;
    bb_allowed = 0;
    ba_opp = 0;
    era = 0;
    iw_issued = 0;
    wild_pitches = 0;
    hbp_issued = 0;
    balks = 0;
    batters_facing_pitcher = 0;
    games_finished = 0;
    runs_given = 0;
    sh_issued = 0;
    sf_issued = 0;
}

bool Basedball::DefaultLT::operator()(Basedball::Player player1, Basedball::Player player2) {
    if (player1.player_id < player2.player_id)
        return true;
    else if (player1.player_id != player2.player_id)
        return false;
    else if (player1.last_name < player2.last_name)
        return true;
    else if (player1.last_name != player2.last_name)
        return false;
    else if (player1.first_name < player2.first_name)
        return true;
    else if (player1.first_name != player2.first_name)
        return false;
    else
        return false;
}

Basedball::Basedball() = default;

void Basedball::read() {
    ifstream file;
    file.open("master.csv");
    file.ignore(224);
    string line_str;
    while(getline(file, line_str)) {
        stringstream line(line_str);
        string player_id;
        getline(line, player_id, ',');

        for (int i = 0; i < 12; i++)
            line.ignore(100, ',');

        string first_name;
        getline(line, first_name, ',');

        string last_name;
        getline(line, last_name, ',');

        for (int i = 0; i < 3; i++)
            line.ignore(100, ',');
        string bats;
        getline(line, bats, ',');

        string throws;
        getline(line, throws, ',');
        Player new_player(player_id, first_name, last_name, bats, throws);
        player_vect.push_back(new_player);
    }
//
//    for(int i = 0; i < player_vect.size(); i++)
//        cout << player_vect[i].player_id << " " << player_vect[i].first_name << " " << player_vect[i].last_name << " " <<player_vect[i].bats << " " << player_vect[i].throws << endl;
    file.close();
    file.clear();
    file.open("fielding.csv");
    file.ignore(76);
    while(getline(file, line_str)) {
        stringstream line(line_str);
        string player_id;
        getline(line, player_id, ',');
//        cout << player_id << endl;
        int first = 0;
        int last = player_vect.size();
        int middle = player_vect.size() / 2;
        int idx;
        while (player_vect[middle].player_id != player_id) { // Binary search to find player in the vector
            if (first > last) {
                idx = -1;
                break;
            } else if (player_vect[middle].player_id < player_id) {
                first = middle + 1;
                middle = (last + first) / 2;
                idx = middle;
            } else {
                last = middle - 1;
                middle = (last + first) / 2;
                idx = middle;
            }
        }
//        cout << player_vect[idx].player_id << endl;
        string year;
        getline(line, year, ',');
        for (int i = 0; i < 3; i++)
            line.ignore(100, ',');
        string position;
        getline(line, position, ',');
        Player::Stats stats;
        player_vect[idx].position = position;
        string games;
        getline(line, games, ',');
        stats.games = stoi(games);
        string games_started;
        getline(line, games_started, ',');
        if (games_started != "")
            stats.games_started = stoi(games_started);
        string inning_outs;
        getline(line, inning_outs, ',');
        if (inning_outs != "")
            stats.inning_outs = stoi(inning_outs);
        string putouts;
        getline(line, putouts, ',');
        if (putouts != "")
            stats.putouts = stoi(putouts);
        string assists;
        getline(line, assists, ',');
        if (assists != "")
            stats.assists = stoi(assists);
        string errors;
        getline(line, errors, ',');
        if (errors != "")
            stats.errors = stoi(errors);
        string double_plays;
        getline(line, double_plays, ',');
        if (double_plays != "")
            stats.double_plays = stoi(double_plays);
        string passed_balls;
        getline(line, passed_balls, ',');
        if (passed_balls != "")
            stats.passed_balls = stoi(passed_balls);
        player_vect[idx].seasons.emplace(stoi(year), stats);
//        player_vect[idx].print(stoi(year));
    }
    file.close();
    file.clear();

    file.open("batting.csv");
    file.ignore(87);
    while(getline(file, line_str)) {
        stringstream line(line_str);
        string player_id;
        getline(line, player_id, ',');
        int first = 0;
        int last = player_vect.size();
        int middle = player_vect.size() / 2;
        int idx;
        while (player_vect[middle].player_id != player_id) { // Binary search to find player in the vector
            if (first > last) {
                idx = -1;
                break;
            } else if (player_vect[middle].player_id < player_id) {
                first = middle + 1;
                middle = (last + first) / 2;
                idx = middle;
            } else {
                last = middle - 1;
                middle = (last + first) / 2;
                idx = middle;
            }
        }
        string year;
        getline(line, year, ',');
        for (int i = 0; i < 4; i++)
            line.ignore(100, ',');
        string at_bats;
        getline(line, at_bats, ',');
        if (at_bats == "")
            at_bats = "0";
        string runs;
        getline(line, runs, ',');
        if (runs == "")
            runs = "0";
        string hits;
        getline(line, hits, ',');
        if (hits == "")
            hits = "0";
        string doubles;
        getline(line, doubles, ',');
        if (doubles == "")
            doubles = "0";
        string triples;
        getline(line, triples, ',');
        if (triples == "")
            triples = "0";
        string home_runs;
        getline(line, home_runs, ',');
        if (home_runs == "")
            home_runs = "0";
        string rbi;
        getline(line, rbi, ',');
        if (rbi == "")
            rbi = "0";
        string stolen_bases;
        getline(line, stolen_bases, ',');
        if (stolen_bases == "")
            stolen_bases = "0";
        string walks;
        getline(line, walks, ',');
        if (walks == "")
            walks = "0";
        string strikeouts;
        getline(line, strikeouts, ',');
        if (strikeouts == "")
            strikeouts = "0";
        string intentional_walks;
        getline(line, intentional_walks, ',');
        if (intentional_walks == "")
            intentional_walks = "0";
        string hit_by_pitch;
        getline(line, hit_by_pitch, ',');
        if (hit_by_pitch == "")
            hit_by_pitch = "0";
        string sac_bunts;
        getline(line, sac_bunts, ',');
        if (sac_bunts == "")
            sac_bunts = "0";
        string sac_flies;
        getline(line, sac_flies, ',');
        if (sac_flies == "")
            sac_flies = "0";
        auto yr = player_vect[idx].seasons.find(stoi(year));
        if (yr != player_vect[idx].seasons.end()) {
            yr->second.at_bats = stoi(at_bats);
            yr->second.runs = stoi(runs);
            yr->second.hits = stoi(hits);
            yr->second.doubles = stoi(doubles);
            yr->second.triples = stoi(triples);
            yr->second.home_runs = stoi(home_runs);
            yr->second.rbi = stoi(rbi);
            yr->second.stolen_bases = stoi(stolen_bases);
            yr->second.walks = stoi(walks);
            yr->second.strikeouts = stoi(strikeouts);
            yr->second.intentional_walks = stoi(intentional_walks);
            yr->second.hit_by_pitch = stoi(hit_by_pitch);
            yr->second.sac_bunts = stoi(sac_bunts);
            yr->second.sac_flies = stoi(sac_flies);
            double batting_avg = stod(hits) / stod(at_bats);
            double slugging = (stod(hits) + stod(doubles) + 2 * stod(triples) + 3 * stod(home_runs)) / stod(at_bats);
            double obp = (stod(hits) + stod(walks) + stod(hit_by_pitch)) / (stod(at_bats) + stod(walks) + stod(hit_by_pitch) + stod(sac_flies));
            double ops = slugging + obp;
            yr->second.batting_avg = batting_avg;
            yr->second.slugging = slugging;
            yr->second.obp = obp;
            yr->second.ops = ops;
        }
        else {
            Player::Stats stats;
            stats.at_bats = stoi(at_bats);
            stats.runs = stoi(runs);
            stats.runs = stoi(hits);
            stats.doubles = stoi(doubles);
            stats.triples = stoi(triples);
            stats.home_runs = stoi(home_runs);
            stats.rbi = stoi(rbi);
            stats.stolen_bases = stoi(stolen_bases);
            stats.walks = stoi(walks);
            stats.strikeouts = stoi(strikeouts);
            stats.intentional_walks = stoi(intentional_walks);
            stats.hit_by_pitch = stoi(hit_by_pitch);
            stats.sac_bunts = stoi(sac_bunts);
            stats.sac_flies = stoi(sac_flies);
            double batting_avg = stod(hits) / stod(at_bats);
            double slugging = (stod(hits) + stod(doubles) + 2 * stod(triples) + 3 * stod(home_runs)) / stod(at_bats);
            double obp = (stod(hits) + stod(walks) + stod(hit_by_pitch)) / (stod(at_bats) + stod(walks) + stod(hit_by_pitch) + stod(sac_flies));
            double ops = slugging + obp;
            stats.batting_avg = batting_avg;
            stats.slugging = slugging;
            stats.obp = obp;
            stats.ops = ops;
            player_vect[idx].seasons.emplace(stoi(year), stats);
        }
        player_vect[idx].print(stoi(year));
    }
}