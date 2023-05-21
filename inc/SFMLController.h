#ifndef PO_SFMLCONTROLLER_H
#define PO_SFMLCONTROLLER_H
#include "Board.h"
#include "SFMLView.h"
#include <SFML/Graphics.hpp>

class SfmlController {
    Board& board;
    SfmlView& view;
public:
    SfmlController(Board& b, SfmlView& v)
        :board(b), view(v){}
    void play(sf::Event event, sf::RenderWindow& window);
};

#endif
