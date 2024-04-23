#include <iostream>
#include <regex>
#include <tabulate/tabulate.hpp>
#include "basedball.h"

void invalid() {
    tabulate::Table inv;
    inv.add_row({"Invalid argument!"});
    inv.add_row({"Please try again :("});
    inv.format().font_color(tabulate::Color::red);
    inv.format().border("");
    inv.format().corner("");
    inv.row(0).format().font_style({tabulate::FontStyle::bold});
    cout << inv << endl;
}

int main() {
    tabulate::Table fancy;
    fancy.add_row({"Loading Database..."});
    fancy.row(0).format().font_style({tabulate::FontStyle::blink});
    cout << fancy << endl;
    Basedball based;

    based.read();
    cout <<  "             ___________          _________            _____________      __________________  \n"
            "            /           \\        /        |           /            /     /                 /\n"
            "           /   ____     /       /   __    |          /       _____/     /_____       _____/\n"
            "          /   /___/    /       /   /  |   |         /       /                /      /\n"
            "         /         ___/       /   /   |   |          \\      \\               /      /\n"
            "        /            \\       /   /____|   |           \\      \\             /      /\n"
            "       /    _____     \\     /    _____    |            \\      \\           /      /            \n"
            "      /    /____/     |    /    /     |   |     _______/      /          /      /          \n"
            "     /               /    /    /      |   |    /             /          /      /\n"
            "     \\______________/    /____/       |___|   /_____________/          /______/\n"
            "         Baseball             Analytics            Search                Tool\n\n"
            "                       (c) 2024 Emily Garcia & Christian Niebauer\n"
            << endl;
    bool run = true;
    unordered_set<int> years;
    for (int i = 1871; i < 2023; i++)
        years.insert(i);
    unordered_set<string> teams;
    teams.insert(based.AL.begin(), based.AL.end());
    teams.insert(based.NL.begin(), based.NL.end());
    teams.insert(based.other.begin(), based.other.end());
    string sort = "last_name";
    unordered_set<string> leagues = {"AL", "NL", "other"};
    unordered_set<string> stats = {"BA", "Throws", "Catches"};

    while (run) {
        cout << "enter a command (type \"help\" for a list of commands):" << endl;
        string input;
        getline(cin, input);
        stringstream iline;
        iline << input;
        string op1;
        getline(iline, op1, ' ');
        regex help_in("help", regex_constants::icase);
        regex stats_in("stats", regex_constants::icase);
        regex year_in("year", regex_constants::icase);
        regex print_in("print", regex_constants::icase);
        regex league_in("league", regex_constants::icase);
        regex team_in("team", regex_constants::icase);
        regex default_in("default", regex_constants::icase);
        regex bast_in("bast", regex_constants::icase);
        regex license_in("license", regex_constants::icase);
        regex player_in("player", regex_constants::icase);
        regex sort_in("sort", regex_constants::icase);
        regex view_in("view", regex_constants::icase);
        regex exit_in("exit", regex_constants::icase);
        regex al_in("al", regex_constants::icase);
        regex nl_in("nl", regex_constants::icase);
        regex other_in("other", regex_constants::icase);

        regex pname_in("\".*\" \".*\"", regex_constants::icase);
        if (regex_match(op1, help_in)) {
            if (input.size() == 4) {
                tabulate::Table comms;
                comms.add_row({"print", "Print a list of players corresponding to selected filters"});
                comms.add_row({"help", "Print a list of commands"});
                comms.add_row({"help stats", "Print a list explaining each statistic"});
                comms.add_row({"help BAST", "Print information about BAST"});
                comms.add_row({"help license", "Print information about BAST's license"});
                comms.add_row({"help <COMMAND>", "Print information for a specific command"});
                comms.add_row({"year <YEAR>", "Show stats from <YEAR> only"});
                comms.add_row({"year <TO> <FROM>", "Show stats between <TO> and <FROM> only (default: 1871-2023)"});
                comms.add_row({"teams <TEAM_1> <TEAM_2> ...", "Show stats for only specified teams (default: all)"});
                comms.add_row({"filters", "Show current value of each filter"});
                comms.add_row({"sort <STAT>", "Sort the output by the specified statistic (default: last_name)"});
                comms.add_row({"league <LEAGUE>", "Show only players from LEAGUE (default: all)"});
                comms.add_row({"stats <STAT_1> <STAT_2>", "Show only selected stats (default: all)"});
                comms.add_row({"default", "Reset all parameters to defaults"});
                comms.add_row({"player <FIRST> <LAST>", "Show only results for specified player"});
                comms.add_row({"view", "View current parameters"});
                comms.add_row({"exit", "Exit BAST"});
                comms.column(0).format().font_color(tabulate::Color::red);
                comms.column(0).format().font_style({tabulate::FontStyle::bold});
                comms.column(0).format().font_background_color(tabulate::Color::blue);
                cout << comms << endl;
            }
            else {
                string op2;
                getline(iline, op2);
                cout << op2 << endl;
                if (regex_match(op2, bast_in)) {
                    cout << "+-----------------------------------------------------------------------------------------------------------+\n"
                            "| Baseball Analytics Search Tool (BAST) is a program designed to comprehensively display and compare        |\n"
                            "| statistics for Major League Baseball players active between 1871 and 2023.                                |\n"
                            "|\t\t\t\t\t\t\t\t\t\t\t\t\t    |\n"
                            "| All data used for this project can be found at http://seanlahman.com/. BAST uses the 2023                 |\n"
                            "| comma-delimited version of the Lahman Baseball Database. Thank you for compiling such                     |\n"
                            "| an awesome database Mr. Lahman.\t\t\t\t\t\t\t\t            |\n"
                            "|\t\t\t\t\t\t\t\t\t\t\t\t\t    |\n"
                            "|\t\t\t\t\t\t\t\t\t\t\t\t\t    |\n"
                            "|\t\t\t\t\t\t\t\t\t\t\t\t\t    |\n"
                            "| This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License cc-by-sa. |\n"
                            "+-----------------------------------------------------------------------------------------------------------+\n\n";
                }
                else if (regex_match(op2, license_in)){
                    // not super important, will implement later
                }
                else if (regex_match(op2, year_in)) {
                    tabulate::Table info;
                    info.add_row({"year", "Select year or range of years to display. Default 1871-2023"});
                    info.add_row({"year 1917","Display selected stats from only 1917"});
                    info.add_row({"year 1917 2005","Display selected stats from 1917 to 2005 (inclusive)"});
                    info.add_row({"year all", "Display selected stats for all years"});
                    info.column(0).format().font_color(tabulate::Color::red);
                    info.column(0).format().font_style({tabulate::FontStyle::bold});
                    info.column(0).format().font_background_color(tabulate::Color::blue);
                    cout << info << endl;
                }
                else if (regex_match(op2, print_in)) {
                    tabulate::Table info;
                    info.add_row({"print", "Print out player data with currently applied filters, takes no arguments"});
                    info.column(0).format().font_color(tabulate::Color::red);
                    info.column(0).format().font_style({tabulate::FontStyle::bold});
                    info.column(0).format().font_background_color(tabulate::Color::blue);
                    info.format().font_align(tabulate::FontAlign::center);
                    cout << info << endl;
                }
                else if (regex_match(op2, player_in)) {
                    tabulate::Table info;
                    info.add_row({"player", "Print data only for the player specified in this command. Player names are\n "
                                            "case-sensitive and surrounded by double quotes. Multiple names should\n"
                                            "be separated by a comma. Do not include any characters with accents or diacritics\n"
                                            "in player names."});
                    info.add_row({"player Jose Abreu", "Display selected statistics for Jose Abreu"});
                    info.add_row({"player all", "Display selected statistics for all players"});
                    info.column(0).format().font_color(tabulate::Color::red);
                    info.column(0).format().font_style({tabulate::FontStyle::bold});
                    info.column(0).format().font_background_color(tabulate::Color::blue);
                    info.column(0)[0].format().padding_top(1);
                    info.format().font_align(tabulate::FontAlign::center);
                    cout << info << endl;
                }

                else if (regex_match(op2, default_in)) {
                    tabulate::Table info;
                    info.add_row({"default", "Reset all settings to the following default values"});
                    info.add_row({"year", "All years"});
                    info.add_row({"league", "All leagues"});
                    info.add_row({"team", "All teams"});
                    info.add_row({"player", "All players"});
                    info.add_row({"sort", "Sort by last name"});
                    info.column(0).format().font_color(tabulate::Color::red);
                    info.column(0).format().font_style({tabulate::FontStyle::bold});
                    info.column(0).format().font_background_color(tabulate::Color::blue);
                    info.format().font_align(tabulate::FontAlign::center);
                    cout << info << endl;
                }

                else if (regex_match(op2, default_in)) {
                    tabulate::Table info;
                    info.add_row({"default", "Reset all settings to the following default values"});
                    info.add_row({"year", "All years"});
                    info.add_row({"league", "All leagues"});
                    info.add_row({"team", "All teams"});
                    info.add_row({"player", "All players"});
                    info.add_row({"sort", "Sort by last name"});
                    info.column(0).format().font_color(tabulate::Color::red);
                    info.column(0).format().font_style({tabulate::FontStyle::bold});
                    info.column(0).format().font_background_color(tabulate::Color::blue);
                    info.format().font_align(tabulate::FontAlign::center);
                    cout << info << endl;
                }

                else {
                    invalid();
                }
            }

        }

        else if (regex_match(op1, league_in)) {
            unordered_set<string> new_lgs;
            vector<string> args;
            string tmp;
            while(getline(iline, tmp, ' '))
                args.push_back(tmp);

            if (args.size() > 3)
                invalid();
            else {
                bool ins = true;
                for (int i = 0; i < args.size(); i++) {
                    if (args[i] != "AL" && args[i] != "NL" && args[i] != "other") {
                        invalid();
                        ins = false;
                        break;
                    }
                    else
                        new_lgs.insert(args[i]);
                }
                if (ins) {
                    leagues = new_lgs;
                    for (int i = 0; i < args.size(); i++)
                        cout << "Added " << args[i] << "!\n";
                }
            }
        }

        else if (regex_match(op1, team_in)) {
            unordered_set<string> new_teams;
            vector<string> args;
            string tmp;
            while(getline(iline, tmp, ' '))
                args.push_back(tmp);
            bool ins = true;
            for (int i = 0; i < args.size(); i++) {
                if (!based.AL.contains(args[i]) && !based.NL.contains(args[i]) && !based.other.contains(args[i])) {
                    invalid();
                    ins = false;
                    break;
                }
                else
                    new_teams.insert(args[i]);
            }
            if (ins) {
                teams = new_teams;
                for (int i = 0; i < args.size(); i++)
                    cout << "Inserted " << args[i] << "!\n";
            }
        }

        else if (regex_match(op1, stats_in)) {
            unordered_set<string> new_stats;
            vector<string> args;
            string tmp;
            while(getline(iline, tmp, ' '))
                args.push_back(tmp);
            bool ins = true;
            for (int i = 0; i < args.size(); i++) {
                if (!based.valid_stats.contains(args[i])) {
                    invalid();
                    ins = false;
                    break;
                }
                else
                    new_stats.insert(args[i]);
            }
            if (ins) {
                stats = new_stats;
                for (int i = 0; i < args.size(); i++)
                    cout << "Inserted " << args[i] << "!\n";
            }
        }

        else if (regex_match(op1, sort_in)) {
            string op2, op3;
            getline(iline, op2, ' ');
            getline(iline, op3);
            Basedball::ComparePlayers* cmp;
            if (op3 != "asc" && op3 != "desc") {
                invalid();
                break;
            }

            if (op2 == "last_name") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareLastName;

                else if (op3 == "desc")
                    cmp = new Basedball::CompareLastNameDesc;

            }

            else if (op2 == "BA") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareByBattingAvg;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareByBattingAvgDesc;
            }

            else if (op2 == "HR") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareByHomeRuns;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareByHomeRunsDesc;
            }

            else if (op2 == "RBI") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareByRBI;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareByRBIDesc;
            }

            else if (op2 == "AB") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareByAtBats;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareByAtBatsDesc;
            }

            else if (op2 == "R") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareRuns;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareRunsDesc;
            }

            else if (op2 == "H") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareHits;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareHitsDesc;
            }

            else if (op2 == "2B") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareDoubles;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareDoublesDesc;
            }

            else if (op2 == "3B") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareTriples;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareTriplesDesc;
            }

            else if (op2 == "SB") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareStolenBases;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareStolenBasesDesc;
            }

            else if (op2 == "CS") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareStealing;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareStealingDesc;
            }

            else if (op2 == "SO") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareStrikes;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareStrikesDesc;
            }

            else if (op2 == "BB") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareWalks;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareWalksDesc;
            }

            else if (op2 == "HBP") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareHitPitch;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareHitPitchDesc;
            }

            else if (op2 == "SH") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareSacs;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareSacsDesc;
            }

            else if (op2 == "SF") {
                if (op3 == "asc")
                    cmp = new Basedball::CompareSacFlies;
                else if (op3 == "desc")
                    cmp = new Basedball::CompareSacFliesDesc;
            }

            else {
                Basedball::CompareSacs cmp;
                invalid();
                break;
            }
            stats.insert(op2);
            cout << "Sorting database..." << endl;
            Basedball::MaxHeap heap(*cmp);
            heap.heapSort(based.player_vect, *cmp, leagues, teams, years);
            tabulate::Table playas;
            tabulate::RowStream r{};
            r << "First Name" << "Last Name" << "Year";
            if (stats.contains("Bats"))
                r << "Bats";
            if (stats.contains("Throws"))
                r << "Throws";
            if (stats.contains("Year"))
                r << "Year";
            if (stats.contains("Team"))
                r << "Team";
            if (stats.contains("League"))
                r << "League";
            if (stats.contains("POS"))
                r << "POS";
            if (stats.contains("BA"))
                r << "BA";
            if (stats.contains("SLG"))
                r << "SLG";
            if (stats.contains("OBP"))
                r << "OBP";
            if (stats.contains("OPS"))
                r << "OPS";
            if (stats.contains("AB"))
                r << "AB";
            if (stats.contains("R"))
                r << "R";
            if (stats.contains("H"))
                r << "H";
            if (stats.contains("2B"))
                r << "2B";
            if (stats.contains("3B"))
                r << "3B";
            if (stats.contains("HR"))
                r << "HR";
            if (stats.contains("RBI"))
                r << "RBI";
            if (stats.contains("SB"))
                r << "SB";
            if (stats.contains("CS"))
                r << "CS";
            if (stats.contains("BB"))
                r << "BB";
            if (stats.contains("SO"))
                r << "SO";
            if (stats.contains("IBB"))
                r << "IBB";
            if (stats.contains("HBP"))
                r << "HBP";
            if (stats.contains("SH"))
                r << "SH";
            if (stats.contains("SF"))
                r << "SF";
            if (stats.contains("GIDP_F"))
                r << "GIDP_F";
            if (stats.contains("G"))
                r << "G";
            if (stats.contains("GS"))
                r << "GS";
            if (stats.contains("InnOuts"))
                r << "InnOuts";
            if (stats.contains("PO"))
                r << "PO";
            if (stats.contains("A"))
                r << "A";
            if (stats.contains("E"))
                r << "E";
            if (stats.contains("DP"))
                r << "DP";
            if (stats.contains("PB"))
                r << "PB";
            if (stats.contains("SB"))
                r << "SB";
            if (stats.contains("CS"))
                r << "CS";
            if (stats.contains("ZR"))
                r << "ZR";
            if (stats.contains("W"))
                r << "W";
            if (stats.contains("L"))
                r << "L";
            if (stats.contains("CG"))
                r << "CG";
            if (stats.contains("SHO"))
                r << "SHO";
            if (stats.contains("SV"))
                r << "SV";
            if (stats.contains("IPouts"))
                r << "IPouts";
            if (stats.contains("H_P"))
                r << "H_P";
            if (stats.contains("ER"))
                r << "ER";
            if (stats.contains("HR_P"))
                r << "HR_P";
            if (stats.contains("BB_P"))
                r << "BB_P";
            if (stats.contains("SO_P"))
                r << "SO_P";
            if (stats.contains("BAOpp"))
                r << "BAOpp";
            if (stats.contains("ERA"))
                r << "ERA";
            if (stats.contains("IBB_P"))
                r << "IBB_P";
            if (stats.contains("WP"))
                r << "WP";
            if (stats.contains("HBP_P"))
                r << "HBP_P";
            if (stats.contains("BK"))
                r << "BK";
            if (stats.contains("BFP"))
                r << "BFP";
            if (stats.contains("GF"))
                r << "GF";
            if (stats.contains("R"))
                r << "R";
            if (stats.contains("SH_P"))
                r << "SH_P";
            if (stats.contains("SF_P"))
                r << "SF_P";
            playas.add_row(r); //
            unordered_set<string> included;
            for (int i = 0; i < based.player_vect.size(); i++) {
                tabulate::RowStream r2{};
                auto s = based.player_vect[i].seasons.begin();
                r2 << based.player_vect[i].first_name << based.player_vect[i].last_name << s->first;
                if (stats.contains("Bats"))
                    r2 << based.player_vect[i].bats;
                if (stats.contains("Throws"))
                    r2 << based.player_vect[i].throws;
                if (stats.contains("POS"))
                    r2 << based.player_vect[i].position;
                if (stats.contains("BA"))
                    r << s->second.batting_avg;
                if (stats.contains("SLG"))
                    r << s->second.slugging;
                if (stats.contains("OBP"))
                    r << s->second.obp;
                if (stats.contains("OPS"))
                    r << s->second.ops;
                if (stats.contains("Team"))
                    r2 << s->second.team;
                if (stats.contains("League")) {
                    if (based.AL.contains(s->second.team))
                        r2 << "AL";
                    else if (based.NL.contains(s->second.team))
                        r2 << "NL";
                    else
                        r2 << "Other";
                }
                if (stats.contains("AB"))
                    r2 << s->second.at_bats;
                if (stats.contains("R"))
                    r2 << s->second.runs;
                if (stats.contains("H"))
                    r2 << s->second.hits;
                if (stats.contains("2B"))
                    r2 << s->second.doubles;
                if (stats.contains("3B"))
                    r2 << s->second.triples;
                if (stats.contains("HR"))
                    r2 << s->second.home_runs;
                if (stats.contains("RBI"))
                    r2 << s->second.rbi;
                if (stats.contains("SB"))
                    r2 << s->second.stolen_bases;
                if (stats.contains("CS"))
                    r2 << s->second.caught_stealing;
                if (stats.contains("BB"))
                    r2 << s->second.walks;
                if (stats.contains("SO"))
                    r2 << s->second.strikeouts;
                if (stats.contains("IBB"))
                    r2 << s->second.intentional_walks;
                if (stats.contains("HBP"))
                    r2 << s->second.hit_by_pitch;
                if (stats.contains("SH"))
                    r2 << s->second.sac_bunts;
                if (stats.contains("SF"))
                    r2 << s->second.sac_flies;
                if (stats.contains("GIDP_F"))
                    r2 << "GIDP_F";
                playas.add_row(r2);
            }
            cout << playas << endl;

        }

        else
            invalid();


//        else if (regex_match(op1, player_in)) {
//            vector<string> args;
//            string tmp;
//            while(getline(iline, tmp, ' '))
//                args.push_back(tmp);
//            for (int i = 0; i < args.size(); i++) {
//                if (!based.AL.contains(args[i]) && !based.NL.contains(args[i]) && !based.other.contains(args[i])) {
//                    teams.clear();
//                    invalid();
//                    break;
//                }
//                else
//                    teams.insert(args[i]);
//            }
//
//        }

    }
    return 0;
}
