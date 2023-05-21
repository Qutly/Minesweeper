#include "../inc/SFMLController.h"

void SfmlController::play(sf::Event event, sf::RenderWindow& window) {

    const float squareSize = 30.f;
    const float squareSpacing = 2.f;
    float totalWidth = (board.getBoardWidth() * squareSize) + ((board.getBoardWidth() - 1) * squareSpacing);
    float totalHeight = (board.getBoardHeight() * squareSize) + ((board.getBoardHeight() - 1) * squareSpacing);
    float startX = (window.getSize().x - totalWidth) / 2.f;
    float startY = (window.getSize().y - totalHeight) / 2.f;

    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            while(board.getGameState() == RUNNING) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                            sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    int xIndex = (mousePos.x - startX) / (squareSize + squareSpacing);
                    int yIndex = (mousePos.y - startY) / (squareSize + squareSpacing);
                    board.revealField(yIndex, xIndex);
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                            sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    int xIndex = (mousePos.x - startX) / (squareSize + squareSpacing);
                    int yIndex = (mousePos.y - startY) / (squareSize + squareSpacing);
                    board.toggleFlag(yIndex, xIndex);
                }
                break;
            }
        default:
            break;
    }
}