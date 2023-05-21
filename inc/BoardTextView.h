#ifndef PO_BOARDTEXTVIEW_H
#define PO_BOARDTEXTVIEW_H
#include "Board.h"

class BoardTextView {

    Board& board;

public:
    BoardTextView(Board &b)
        :board(b){}
    void display();
};


#endif
