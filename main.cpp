#include <iostream>
#include <regex>
#include <tabulate/tabulate.hpp>
#include "basedball.h"

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
    while (run) {
        cout << "enter a command (type \"help\" for a list of commands):" << endl;
        string years = "all";
        string teams = "all";
        string sort = "last_name";
        string league = "all";
        string player;
        string input;
        getline(cin, input);
        stringstream iline;
        iline << input;
        string op1;
        getline(iline, op1, ' ');
        regex help_in("help", regex_constants::icase);
        regex stats_in("stats", regex_constants::icase);
        regex years_in("year", regex_constants::icase);
        regex print_in("print", regex_constants::icase);
        regex league_in("league", regex_constants::icase);
        regex default_in("default", regex_constants::icase);
        regex bast_in("bast", regex_constants::icase);
        regex license_in("license", regex_constants::icase);
        regex player_in("player", regex_constants::icase);
        regex sort_in("sort", regex_constants::icase);
        regex exit_in("exit", regex_constants::icase);
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
                comms.add_row({"player <FIRST_1> <LAST_1>", "Show only results for specified players"});
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
                else if (regex_match(op2, years_in)) {
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
                    info.add_row({"player", "Print data only for players specified in this command. Player names are\n "
                                            "case-sensitive and surrounded by double quotes. Multiple names should\n"
                                            "be separated by a comma. Do not include any characters with accents or diacritics\n"
                                            "in player names."});
                    info.add_row({"player Jose Abreu", "Display selected statistics for Jose Abreu"});
                    info.add_row({"player Jose Abreu, Jake Burger", "Display selected statistics for Jose Abreu and Jake Burger"});
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
                    tabulate::Table inv;
                    inv.add_row({"Invalid argument!"});
                    inv.add_row({"Please try again :("});
                    inv.format().background_color(tabulate::Color::red);
                    inv.row(0).format().font_style({tabulate::FontStyle::bold});
                    cout << inv << endl;
                }
            }

        }
    }
    return 0;
}
