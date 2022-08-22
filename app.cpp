#include <iostream>
#include <ctype.h>
#include "game.h"
using namespace std;

int main() {
    // host or client?
    char mode = 0;

    while (mode != 'j' && mode != 'h') {
        cout << "(H)ost or (J)oin? ";
        cin >> mode;
        mode = tolower(mode);
    }

    Game g(mode=='h');

    return 0;
}
