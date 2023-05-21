#ifndef PO_TEXTCONTROLLER_H
#define PO_TEXTCONTROLLER_H
#include "Board.h"
#include "BoardTextView.h"

class TextController {
    Board& board;
    BoardTextView& view;
public:
    TextController(Board& b, BoardTextView& v)
        :board(b), view(v){}
    void play();
};


#endif
