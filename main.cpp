#include <iostream>
#include "basedball.h"

int main() {
    Basedball based;
    based.read();
    cout << "        ____________\n"
            "           /    __     /\n"
            "          /    /__/   /\n"
            "         /           /\n"
            "        /           \\\n"
            "       /             \\\n"
            "      |              |\n"
            "      /______________/"
    << endl;
    return 0;
}
