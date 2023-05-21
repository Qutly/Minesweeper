#include "../inc/TextController.h"
#include <iostream>
using namespace std;

void TextController::play() {
    int option, x, y;

    while(board.getGameState() == RUNNING) {
        cout << "1. Odkryj pole " << "2. Postaw flage" << "\n";
        cin >> option;
        cout << "Podaj współrzędną x" << "\n";
        cin >> x;
        cout << "Podaj współrzędną y" << "\n";
        cin >> y;
            switch (option) {
                case 1:
                    board.revealField(y, x);
                    view.display();
                    break;
                case 2:
                    board.toggleFlag(y, x);
                    view.display();
                    break;
            }
    }
}
