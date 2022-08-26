#include <iostream>
#include <unistd.h>
#include <ctype.h>
#include "game.hpp"
using namespace std;

#define PORT 14201

int main() {
    // host or client?
    char mode = 0;

    while (mode != 'j' && mode != 'h') {
        cout << "(H)ost or (J)oin? ";
        cin >> mode;
        mode = tolower(mode);
    }

    Game g(mode=='h', PORT);

    while(1){
        sleep(5);
    }

    return 0;
}
