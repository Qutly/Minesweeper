#include <iostream>
#include <cmath>
#include <cstdlib>
#include "../inc/Board.h"

using namespace std;

Board::Board(int width, int height, GameMode mode) {

    boardWidth = width;
    boardHeight = height;
    gameMode = mode;

    switch (mode) {
        case DEBUG:
            debugMode(boardWidth, boardHeight);
            debug_display(boardWidth, boardHeight);
            break;
        case EASY: {
            minesAmount = ceil((boardWidth * boardHeight) * 0.1);
            randomMines(boardWidth, boardHeight, minesAmount);
            debug_display(boardWidth, boardHeight);
            break;
        }
        case NORMAL: {
            minesAmount = ceil((boardWidth * boardHeight) * 0.2);
            randomMines(boardWidth, boardHeight, minesAmount);
            debug_display(boardWidth, boardHeight);
        }    break;
        case HARD: {
            minesAmount = ceil((boardWidth * boardHeight) * 0.3);
            randomMines(boardWidth, boardHeight, minesAmount);
            debug_display(boardWidth, boardHeight);
            break;
        }
    }
}

// FUNKCJA LOSUJACA

void Board::randomMines(int width, int height, int size) {
    Field f{};
    int i, x, y;
    srand(time(NULL));
    for(i=0; i<size; i++) {
        f.hasMine = true;
        while(true) {
            x = rand() % width;
            y = rand() % height;
            if(!board[y][x].hasMine) {
                board[y][x] = f;
                break;
            }
        }
    }
}

// FUNKCJE DEBUG

void Board::debugMode(int width, int height) {
    Field f{};
    int i,j, counter = 0;
    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            if(i==j || i==0 || (i%2==0 && j==0)) {
                f.hasMine = true;
                board[i][j] = f;
                counter ++;
            }
        }
    }
    minesAmount = counter;
}

// FUNKCJA WYPISUJACA

void Board::debug_display(int width, int height) const {
    int i, j, k;
    cout << "     ";
    for(k=0; k<width; k++) {
        cout << (k<=9 ? to_string(k) + "    " : to_string(k) + "   ");
    }
    cout << endl;

    for(i=0; i<height; i++) {
        for(j=0; j<width; j++) {
            cout
                    << (j==0 ? (i<=9 ? to_string(i) + "  ": to_string(i) +  " ") : "")
                    << "["
                    << (board[i][j].hasMine ? "M" : ".")
                    << (board[i][j].isRevealed ? "o" : ".")
                    << (board[i][j].hasFlag ? "f" : ".")
                    << "]" << (j == width - 1 ? "\n" : "");
        }
    }
}

int Board::getBoardWidth() const {
    return boardWidth;
}

int Board::getBoardHeight() const {
    return boardHeight;
}

int Board::getMineCount() const {
    return minesAmount;
}

int Board::countMines(int row, int col) const {
    int i, j, minesCounter = 0;

    if(!board[row][col].isRevealed) return -1;
    if(row < 0 || row > boardHeight - 1 || col < 0 || col > boardWidth - 1) return -1;

    if(board[row][col].hasMine) minesCounter--;

    for(i=row-1; i<=row+1; i++) {
        for(j=col-1; j<=col+1; j++) {
            if(board[i][j].hasMine && i>=0 && j>=0)
                minesCounter++;
        }
    }
    return minesCounter;
}

bool Board::hasMine(int row, int col) const {
    if(board[row][col].hasMine) return true;
}

bool Board::isFirstMove() const {
    int i,j;

    for(i=0; i<boardHeight; i++) {
        for(j=0; j<boardWidth; j++) {
            if(board[i][j].isRevealed)
                return false;
        }
    }
    return true;
}

bool Board::hasFlag(int row, int col) const {
    if(board[row][col].hasFlag) return true;
    if((row < 0 || row > boardHeight - 1 || col < 0 || col > boardWidth - 1) ||
        !board[row][col].hasFlag ||
         board[row][col].isRevealed) return false;
}

void Board::toggleFlag(int row, int col) {
    if(!board[row][col].hasFlag) board[row][col].hasFlag = true;
}

void Board::revealField(int row, int col) {
    if(row < 0 || row > boardHeight - 1 || col < 0 || col > boardWidth - 1) return;

    if (!board[row][col].isRevealed && !board[row][col].hasMine) {
        board[row][col].isRevealed = true;
        if(countMines(row, col) == 0) {
            for(int i=row-1; i<=row+1; i++) {
                for(int j=col-1; j<=col+1; j++) {
                    revealField(i,j);
                }
            }
        }
    }
    if(!board[row][col].isRevealed && board[row][col].hasMine) {
        if(isFirstMove() && gameMode != DEBUG) {
            randomMines(boardWidth, boardHeight, 1);
            board[row][col].hasMine = false;
            board[row][col].isRevealed = true;
        } else {
            board[row][col].isRevealed = true;
            getGameState();
        }
    }
}

bool Board::isRevealed(int row, int col) const {
    if(board[row][col].isRevealed) return true;
    return false;
}

GameState Board::getGameState() const {
    int i, j, counter = 0, condition = (boardWidth * boardHeight) - getMineCount();

    for (i=0; i<boardHeight; i++) {
        for (j = 0; j < boardWidth; j++) {
            if (board[i][j].isRevealed && board[i][j].hasMine) {
                return FINISHED_LOSS;
            }
        }
    }
    for (i=0; i<boardHeight; i++) {
        for (j = 0; j < boardWidth; j++) {
            if (board[i][j].isRevealed && !board[i][j].hasMine) {
                counter++;
                if (counter == condition) {
                    return FINISHED_WIN;
                }
            }
        }
    }
    for (i=0; i<boardHeight; i++) {
        for (j = 0; j < boardWidth; j++) {
            if (!board[i][j].isRevealed && !board[i][j].hasMine) {
                return RUNNING;
            }
        }
    }
}

char Board::getFieldInfo(int row, int col) const {
    int mines = countMines(row,col);
    if(row < 0 || row > boardHeight - 1 || col < 0 || col > boardWidth - 1) return '#';
    if(!board[row][col].isRevealed && board[row][col].hasFlag) return 'F';
    if(!board[row][col].isRevealed && !board[row][col].hasFlag) return '_';
    if(board[row][col].isRevealed && board[row][col].hasMine) return 'x';
    if(board[row][col].isRevealed && !board[row][col].hasMine && mines==0) return ' ';
    if(board[row][col].isRevealed && !board[row][col].hasMine && mines!=0) return char(mines);
}