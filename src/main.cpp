#include "../inc/Board.h"
#include "../inc/SFMLView.h"
#include "../inc/SFMLController.h"
#include <SFML/Graphics.hpp>

int main()
{
    Board board(10, 10, EASY);
    SfmlView view (board);
    SfmlController ctrl(board, view);
    sf::RenderWindow window(sf::VideoMode(board.getBoardHeight() * 55, board.getBoardWidth() * 55), "Minesweeper", sf::Style::Titlebar | sf::Style::Close & ~sf::Style::Resize);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    float centerX = static_cast<float>(desktop.width - window.getSize().x) / 2.0f;
    float centerY = static_cast<float>(desktop.height - window.getSize().y) / 2.0f;

    window.setPosition(sf::Vector2i(static_cast<int>(centerX), static_cast<int>(centerY)));

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ctrl.play(event, window);
        }
        window.clear();
        view.draw(window);
        window.display();
    }

    return 0;
}

