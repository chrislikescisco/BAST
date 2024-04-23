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

Basedball::Player::PStats::PStats() {
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

unordered_set<string> Basedball::pitchers;

void Basedball::Player::print() {
    cout << "Player ID: " << player_id << endl << "Name: " << first_name << ' ' << last_name << endl <<"Bats: " << bats
    << endl << "Throws: " << throws << endl;
    for (auto iter = seasons.begin(); iter != seasons.end(); iter++) {
        cout << iter->first << ": " << endl;
        iter->second.print();
        if (pitchers.find(player_id) != pitchers.end()) {
            cout << iter->first << endl;
            pitching_seasons[iter->first].print();
        }
    }

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

void Basedball::Player::PStats::print() {
    cout << fixed << setprecision(3) << "Wins: " << wins << endl << "Losses: " << losses << endl << "Complete Games: "
    << complete_games << endl << "Shutouts: " << shutouts << endl << "Saves: " << saves << endl <<
    "Innings Pitched (outs): " << ip_outs << endl << "Hits Allowed: " << hits_allowed << endl << "Home Runs (issued): "
    << hr_allowed << endl << "Strikeouts (issued): " << so_issued << endl << "Walks (issued): " << bb_allowed << endl <<
    "Batting Average (Opponents): " << ba_opp << endl << "ERA: " << era << endl << "Intentional Walks (issued): :" <<
    iw_issued << endl << "Wild Pitches: " << wild_pitches << endl << "HBP (issued): " << hbp_issued << endl << "Balks: "
    << balks << endl << "Batters Facing Pitcher: " << batters_facing_pitcher << "Games Finished: " << games_finished <<
    endl << "Runs (issued): " << runs_given << endl << "Sacrifice Bunts (issued): " << sh_issued << endl <<
    "Sacrifice Flys (issued): " << sf_issued << endl;
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

int Basedball::find(string player_id) {
    int idx;
    int first = 0;
    int last = player_vect.size();
    int middle = player_vect.size() / 2;
    while (player_vect[middle].player_id != player_id) { // Binary search to find player in the vector
//            cout << "first: " << first << " middle: " << middle << " last: " << last << " ID: " << player_vect[middle].player_id << endl;
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
    return idx;
}

Basedball::Basedball() = default;

const unordered_set<string> Basedball::AL = {"ANA", "BAL", "BLA", "BOS", "CAL", "CHA", "CLE", "DET",
                                       "HOU", "KC1", "KCA", "LAA", "MIN", "ML4", "MLA", "NYA",
                                       "OAK", "PHA", "SE1", "SEA", "SLA", "TBA", "TEX", "TOR",
                                       "WS1", "WS2", };
const unordered_set<string> Basedball::NL = {"ARI", "ATL", "BFN", "BLN", "BRO", "BSN", "CHN", "CIN",
                                       "CL2", "CL4", "CN1", "COL", "DTN", "FLO", "HAR", "HOU",
                                       "IN1", "IN3", "KCN", "LAN", "LS1", "LS3", "MIA", "MIL",
                                       "ML1", "ML2", "MON", "NY1", "NY3", "NYN", "PHI", "PHN",
                                       "PIT", "PRO", "SDN", "SFN", "SL3", "SL5", "SLN", "SR1",
                                       "TRN", "WAS", "WOR", "WS8"};
const unordered_set<string> Basedball::other = {"BL2", "BR3", "BR4", "BS2", "CL3", "CL5", "CL6",
                                          "CN2", "CN3", "IN2", "KC2", "LS2", "ML3", "NY4", "PH4",
                                          "PT1", "RC2", "RIC", "SL4", "SR2", "TL1", "TL2", "WS7",
                                          "WS9", "BLF", "BRF", "BUF", "CHF", "KCF", "NEW", "PTF",
                                          "SLF", "BL1", "BR1", "BR2", "BS1", "CH1", "CH2", "CL1",
                                          "ELI", "FW1", "HR1", "KEO", "MID", "NH1", "NY2", "PH1",
                                          "PH2", "PH3", "RC1", "SL1", "SL2", "TRO", "WS3", "WS4",
                                          "WS6", "BFP", "BRP", "BSP", "CHP", "CLP", "NYP", "PHP",
                                          "PTP", "ALT", "BLU", "BSU", "CHU", "CNU", "KCU", "MLU",
                                          "PHU", "SLU", "SPU", "WIL", "WSU"};
const unordered_set<string> Basedball::valid_stats = {"Bats", "Throws", "Team", "League", "AB", "R",
                                                      "H", "2B", "3B", "HR", "RBI", "SB", "CS", "BB", "SO",
                                                      "IBB", "HBP", "SH", "SF", "GIDP_F", "POS", "G", "GS",
                                                      "InnOuts", "PO", "A", "E", "DP", "PB", "SB", "CS", "ZR",
                                                      "W", "L", "CG", "SHO", "SV", "IPouts", "H_P", "ER", "HR_P",
                                                      "BB_P", "SO_P", "BAOpp", "ERA", "IBB_P", "WP", "HBP_P", "BK",
                                                      "BFP", "GF", "R", "SH_P", "SF_P"};

void Basedball::read() {
    ifstream file;
    file.open("People.csv");
    file.ignore(40);
    string line_str;
    while(getline(file, line_str)) {
        stringstream line(line_str);
        string player_id;
        getline(line, player_id, ',');

        string first_name;
        getline(line, first_name, ',');

        string last_name;
        getline(line, last_name, ',');

        string bats;
        getline(line, bats, ',');

        string throws;
        getline(line, throws);
        Player new_player(player_id, first_name, last_name, bats, throws);
        player_vect.push_back(new_player);
    }
//
//    for(int i = 0; i < player_vect.size(); i++)
//        cout << player_vect[i].player_id << " " << player_vect[i].first_name << " " << player_vect[i].last_name << " " <<player_vect[i].bats << " " << player_vect[i].throws << endl;
    file.close();
    file.clear();
    file.open("Fielding.csv");
    file.ignore(67);
    while(getline(file, line_str)) {
        stringstream line(line_str);
        string player_id;
        getline(line, player_id, ',');
        int first = 0;
        int last = player_vect.size();
        int middle = player_vect.size() / 2;

        int idx;
        while (player_vect[middle].player_id != player_id) { // Binary search to find player in the vector
//            cout << "first: " << first << " middle: " << middle << " last: " << last << " ID: " << player_vect[middle].player_id << endl;
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
        string team_id;
        getline(line, team_id, ',');
        string lg_id;
        getline(line, lg_id, ',');
        string position;
        getline(line, position, ',');
        player_vect[idx].position = position;
        Player::Stats stats;
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
        string stolen_bases_allowed;
        getline(line, stolen_bases_allowed, ',');
        if (stolen_bases_allowed != "")
            stats.stolen_bases_allowed = stoi(stolen_bases_allowed);
        string caught_stealing_inf;
        getline(line, caught_stealing_inf, ',');
        if (caught_stealing_inf != "")
            stats.caught_stealing_inf = stoi(caught_stealing_inf);
        string zone_rating;
        getline(line, zone_rating);
        if (zone_rating != "")
            stats.zone_rating = stoi(zone_rating);
        player_vect[idx].seasons.emplace(stoi(year), stats);
//        player_vect[idx].print(stoi(year));
    }
    file.close();
    file.clear();

    file.open("Batting.csv");
    file.ignore(79);
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
        string team_id;
        getline(line, team_id, ',');
        string lg_id;
        getline(line, lg_id, ',');
        string at_bats;
        getline(line, at_bats, ',');
        if (at_bats == "") // Might replace with -1 instead to signify "Not found". Thoughts?
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
        string caught_stealing;
        getline(line, caught_stealing, ',');
        if (caught_stealing == "")
            caught_stealing = "0";
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
        string groundouts;
        getline(line, groundouts);
        if (groundouts == "" )
            groundouts = "0";
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
            yr->second.caught_stealing = stoi(caught_stealing);
            yr->second.walks = stoi(walks);
            yr->second.strikeouts = stoi(strikeouts);
            yr->second.intentional_walks = stoi(intentional_walks);
            yr->second.hit_by_pitch = stoi(hit_by_pitch);
            yr->second.sac_bunts = stoi(sac_bunts);
            yr->second.sac_flies = stoi(sac_flies);
            yr->second.groundouts = stoi(groundouts);
            yr->second.team = team_id;
            double batting_avg = 0;
            double obp = 0;
            double slugging = 0;
            double ops = 0;
            if((stod(at_bats) + stod(walks) + stod(hit_by_pitch) + stod(sac_flies)) != 0)
                obp = (stod(hits) + stod(walks) + stod(hit_by_pitch)) / (stod(at_bats) + stod(walks) + stod(hit_by_pitch) + stod(sac_flies));
            if (stoi(at_bats) != 0) {
                batting_avg = stod(hits) / stod(at_bats);
                slugging =(stod(hits) + stod(doubles) + 2 * stod(triples) + 3 * stod(home_runs)) / stod(at_bats);
                ops = slugging + obp;

            }
            yr->second.batting_avg = batting_avg;
            yr->second.slugging = slugging;
            yr->second.obp = obp;
            yr->second.ops = ops;
        }
        else {
            Player::Stats stats;
            stats.at_bats = stoi(at_bats);
            stats.runs = stoi(runs);
            stats.hits = stoi(hits);
            stats.doubles = stoi(doubles);
            stats.triples = stoi(triples);
            stats.home_runs = stoi(home_runs);
            stats.rbi = stoi(rbi);
            stats.stolen_bases = stoi(stolen_bases);
            stats.caught_stealing = stoi(caught_stealing);
            stats.walks = stoi(walks);
            stats.strikeouts = stoi(strikeouts);
            stats.intentional_walks = stoi(intentional_walks);
            stats.hit_by_pitch = stoi(hit_by_pitch);
            stats.sac_bunts = stoi(sac_bunts);
            stats.sac_flies = stoi(sac_flies);
            stats.groundouts = stoi(groundouts);
            stats.team = team_id;
            double batting_avg = 0;
            double obp = 0;
            double slugging = 0;
            double ops = 0;
            if((stod(at_bats) + stod(walks) + stod(hit_by_pitch) + stod(sac_flies)) != 0)
                obp = (stod(hits) + stod(walks) + stod(hit_by_pitch)) / (stod(at_bats) + stod(walks) + stod(hit_by_pitch) + stod(sac_flies));
            if (stoi(at_bats) != 0) {
                batting_avg = stod(hits) / stod(at_bats);
                slugging =(stod(hits) + stod(doubles) + 2 * stod(triples) + 3 * stod(home_runs)) / stod(at_bats);
                ops = slugging + obp;

            }
            stats.batting_avg = batting_avg;
            stats.slugging = slugging;
            stats.obp = obp;
            stats.ops = ops;
            player_vect[idx].seasons.emplace(stoi(year), stats);
        }
//        player_vect[idx].print(stoi(year));
    }

    file.close();
    file.clear();
    file.open("Pitching.csv");
    file.ignore(102);

    while(getline(file, line_str)) {
        stringstream line(line_str);
        string player_id;
        getline(line, player_id, ',');
        pitchers.insert(player_id);
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
        string team_id;
        getline(line, team_id, ',');
        string lg_id;
        getline(line, lg_id, ',');
        string wins;
        getline(line, wins, ',');
        if (wins == "")
            wins = "0";
        string losses;
        if (losses == "")
            losses = "0";
        getline(line, losses, ',');
        string complete_games;
        getline(line, complete_games, ',');
        if (complete_games == "")
            complete_games = "0";
        string shutouts;
        getline(line, shutouts, ',');
        if (shutouts == "")
            shutouts = "0";
        string saves;
        getline(line, saves, ',');
        if (saves == "")
            saves = "0";
        string ip_outs;
        getline(line, ip_outs, ',');
        if (ip_outs == "")
            ip_outs = "0";
        string hits_allowed;
        getline(line, hits_allowed, ',');
        if (hits_allowed == "")
            hits_allowed = "0";
        string earned_runs;
        getline(line, earned_runs, ',');
        if (earned_runs == "")
            earned_runs = "0";
        string hr_allowed;
        getline(line, hr_allowed, ',');
        if (hr_allowed == "")
            hr_allowed = "0";
        string bb_allowed;
        getline(line, bb_allowed, ',');
        if (bb_allowed == "")
            bb_allowed = "0";
        string so_issued;
        getline(line, so_issued, ',');
        if (so_issued == "")
            so_issued = "0";
        string ba_opp;
        getline(line, ba_opp, ',');
        if (ba_opp == "")
            ba_opp = "0";
        string era;
        getline(line, era, ',');
        if (era == "")
            era = "0";
        string iw_issued;
        getline(line, iw_issued, ',');
        if (iw_issued == "")
            iw_issued = "0";
        string wild_pitches;
        getline(line, wild_pitches, ',');
        if (wild_pitches == "")
            wild_pitches = "0";
        string hbp_issued;
        getline(line, hbp_issued, ',');
        if (hbp_issued == "")
            hbp_issued = "0";
        string balks;
        getline(line, balks, ',');
        if (balks == "")
            balks = "0";
        string batters_facing_pitcher;
        getline(line, batters_facing_pitcher, ',');
        if (batters_facing_pitcher == "")
            batters_facing_pitcher = "0";
        string games_finished;
        getline(line, games_finished, ',');
        if (games_finished == "")
            games_finished = "0";
        string runs_given;
        getline(line, runs_given, ',');
        if (runs_given == "")
            runs_given = "0";
        string sh_issued;
        getline(line, sh_issued, ',');
        if (sh_issued == "")
            sh_issued = "0";
        string sf_issued;
        getline(line, sf_issued);
        if (sf_issued == "")
            sf_issued = "0";
        auto yr = player_vect[idx].pitching_seasons.find(stoi(year));
        if (yr != player_vect[idx].pitching_seasons.end()) {
            yr->second.wins = stoi(wins);
            yr->second.losses = stoi(losses);
            yr->second.complete_games = stoi(complete_games);
            yr->second.shutouts = stoi(shutouts);
            yr->second.saves = stoi(saves);
            yr->second.ip_outs = stoi(ip_outs);
            yr->second.hits_allowed = stoi(hits_allowed);
            yr->second.hr_allowed = stoi(hr_allowed);
            yr->second.so_issued = stoi(so_issued);
            yr->second.bb_allowed = stoi(bb_allowed);
            yr->second.ba_opp = stoi(ba_opp);
            yr->second.so_issued = stoi(so_issued);
            yr->second.bb_allowed = stoi(bb_allowed);
            yr->second.ba_opp = stoi(ba_opp);
            yr->second.era = stod(era);
            yr->second.iw_issued = stoi(iw_issued);
            yr->second.wild_pitches = stoi(wild_pitches);
            yr->second.hbp_issued = stoi(hbp_issued);
            yr->second.balks = stoi(balks);
            yr->second.batters_facing_pitcher = stoi(batters_facing_pitcher);
            yr->second.games_finished = stoi(games_finished);
            yr->second.runs_given = stoi(runs_given);
            yr->second.sh_issued = stoi(sh_issued);
            yr->second.sf_issued = stoi(sf_issued);
            yr->second.team = team_id;
        }
        else {
            Player::PStats pstats;
            pstats.wins = stoi(wins);
            pstats.losses = stoi(losses);
            pstats.complete_games = stoi(complete_games);
            pstats.shutouts = stoi(shutouts);
            pstats.saves = stoi(saves);
            pstats.ip_outs = stoi(ip_outs);
            pstats.hits_allowed = stoi(hits_allowed);
            pstats.hr_allowed = stoi(hr_allowed);
            pstats.so_issued = stoi(so_issued);
            pstats.bb_allowed = stoi(bb_allowed);
            pstats.ba_opp = stoi(ba_opp);
            pstats.so_issued = stoi(so_issued);
            pstats.bb_allowed = stoi(bb_allowed);
            pstats.ba_opp = stoi(ba_opp);
            pstats.era = stod(era);
            pstats.iw_issued = stoi(iw_issued);
            pstats.wild_pitches = stoi(wild_pitches);
            pstats.hbp_issued = stoi(hbp_issued);
            pstats.balks = stoi(balks);
            pstats.batters_facing_pitcher = stoi(batters_facing_pitcher);
            pstats.games_finished = stoi(games_finished);
            pstats.runs_given = stoi(runs_given);
            pstats.sh_issued = stoi(sh_issued);
            pstats.sf_issued = stoi(sf_issued);
            pstats.team = team_id;
            player_vect[idx].pitching_seasons.emplace(stoi(year), pstats);
        }
    }
//    for (int i = 0; i < player_vect.size(); i++)
//        player_vect[i].print();
}