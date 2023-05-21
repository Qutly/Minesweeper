#include "../inc/BoardTextView.h"



void BoardTextView::display() {
    int i, j, k;

    int width = board.getBoardWidth();
    int height = board.getBoardHeight();

    cout << "     ";

    for (k = 0; k < width; k++) {
        cout << (k <= 9 ? to_string(k) + "    " : to_string(k) + "   ");
    }

    cout << endl;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cout
                    << (j == 0 ? (i <= 9 ? to_string(i) + "  " : to_string(i) + " ") : "")
                    << "["
                    << (board.isRevealed(i,j) && board.hasMine(i,j) ? "M": ".")
                    << (board.isRevealed(i,j) ? "o" : ".")
                    << (board.hasFlag(i,j) ? "f" : ".")
                    << "]" << (j == width - 1 ? "\n" : "");
        }
    }
}
