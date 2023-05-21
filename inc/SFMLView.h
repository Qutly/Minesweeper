#ifndef PO_SFMLVIEW_H
#define PO_SFMLVIEW_H
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>

class SfmlView {
    Board& board;
public:
    SfmlView(Board &b)
            :board(b){}
    void draw(sf::RenderWindow& window);
};

#endif

//const float squareSize = 30.f;
//const float squareSpacing = 2.f;
//float totalWidth = (width * squareSize) + ((width - 1) * squareSpacing);
//float totalHeight = (height * squareSize) + ((height - 1) * squareSpacing);
//float startX = (window.getSize().x - totalWidth) / 2.f;
//float startY = (window.getSize().y - totalHeight) / 2.f;