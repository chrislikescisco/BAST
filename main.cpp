#include <iostream>
#include "basedball.h"

int main() {
    cout << "Loading Database..." << endl;
    Basedball based;
    based.read();
    cout << "             ___________           _________            ______________     __________________  \n"
            "            /           \\         /        |           /             /    /                 /\n"
            "           /    ,       /        /   __    |          /       ______/    /_____       _____/\n"
            "          /            /        /   /  |   |         /       /                /      /\n"
            "         /    ________/        /   /   |   |          \\      \\               /      /\n"
            "        /            /        /   /____|   |           \\      \\             /      /\n"
            "       /    ,____,    \\      /    _____|   |            \\      \\           /      /            \n"
            "      |    /____/      \\    /    /     |   |     _______/      /          /      /          \n"
            "      |                /   /    /      |   |    /             /          /      /\n"
            "      \\_______________/   /__ _/       |_ _|   /_____________/          /______/\n"
            "          Baseball            Analysis            Search                 Tool\n\n"
            "                     (c) 2024 Emily Garcia & Christian Niebauer\n\n"
    << endl;
    bool run = true;
    while (run) {
        cout << "Enter a command (type \"help\" for a list of commands):" << endl;
        string input;
        string years = "all";
        string teams = "all";
        getline(cin, input);
        if (input ==  "help") {
            cout << "print -- print a list of players corresponding to selected filters\n"
                    "help -- print a list of commands\n"
                    "help stats -- print a list explaining each statistic\n"
                    "help BAST -- print information about BAST\n"
                    "help <COMMAND> -- print information for a specific command\n"
                    "years <YEAR> -- show stats from <YEAR> only\n"
                    "years <TO> <FROM_> -- show stats between <TO> and <FROM> only (default: 1871-2023)\n"
                    "teams <TEAM_1> <TEAM_2> ... -- show stats for only specified teams (default: all)\n"
                    "filters -- show current value of each filter\n"
                    "sort <STAT> -- sort the output by the specified statistic (default: last_name)\n"
                    "league <LEAGUE> -- show only players from LEAGUE (default: all)\n"
                    "stats <STAT_1> <STAT_2> -- show only selected stats (default: all)\n"
                    "default -- reset all parameters to defaults\n"
                    "player \"<FIRST_1> <LAST_1>\" \"<FIRST_2> <LAST_2>\" -- show only results for specified players\n"
                    "exit -- exit BAST\n";
        }
    }
    return 0;
}
