#ifndef PO_BOARD_H
#define PO_BOARD_H

#include <string>
#include <iostream>

using namespace std;

enum GameMode { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
public:
    Field(): hasMine(false), hasFlag(false), isRevealed(false){}
};

class Board {
    Field board[100][100]{};
    int boardWidth;
    int boardHeight;
    int minesAmount;
    char gameMode;

public:
    Board(int width, int height, GameMode mode);
    void debug_display(int width, int height) const;
    void randomMines(int width, int height, int size);
    bool isFirstMove() const;
    void debugMode(int width, int height);
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int row, int col) const;
    bool hasMine(int row, int col) const;
    bool hasFlag(int row, int col) const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);
    bool isRevealed(int row, int col) const;
    GameState getGameState() const;
    char getFieldInfo(int row, int col) const;
};



#endif