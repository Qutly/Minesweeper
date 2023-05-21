#include "../inc/SFMLView.h"

void SfmlView::draw(sf::RenderWindow& window) {

    int i,j;
    const int width = board.getBoardWidth();
    const int height = board.getBoardHeight();

    sf::Texture textureFlag;
    sf::Texture textureMine;
    sf::Font font;
    sf::Text text;
    sf::Text textEndgameLost("YOU LOST!", font);
    sf::Text textEndgameWin("YOU WIN!", font);
    sf::RectangleShape squares[height][width];

    const float squareSize = 30.f;
    const float squareSpacing = 2.f;
    float totalWidth = (width * squareSize) + ((width - 1) * squareSpacing);
    float totalHeight = (height * squareSize) + ((height - 1) * squareSpacing);
    float startX = (window.getSize().x - totalWidth) / 2.f;
    float startY = (window.getSize().y - totalHeight) / 2.f;

    for (int x = 0; x < board.getBoardHeight(); x++) {
        for (int y = 0; y < board.getBoardWidth(); y++) {
            float posX = startX + (x * (squareSize + squareSpacing));
            float posY = startY + (y * (squareSize + squareSpacing));
            squares[y][x].setSize(sf::Vector2f(squareSize, squareSize));
            squares[y][x].setPosition(posX, posY);
            squares[y][x].setFillColor(sf::Color(200, 200, 200));
            if (board.getFieldInfo(y, x) == '_') {
                window.draw(squares[y][x]);
            }
            if (board.getFieldInfo(y, x) == 'F') {
                if (textureFlag.loadFromFile("../assets/flag.png")) {
                    squares[y][x].setTexture(&textureFlag);
                    window.draw(squares[y][x]);
                    squares[y][x].setTexture(nullptr);
                }
            }
            if (board.getFieldInfo(y, x) == 'x') {
                if (textureMine.loadFromFile("../assets/mine.png")) {
                    squares[y][x].setTexture(&textureMine);
                    window.draw(squares[y][x]);
                }
            }
            if (board.getFieldInfo(y, x) == ' ') {
                squares[y][x].setFillColor(sf::Color(140,140,140));
                window.draw(squares[y][x]);
            }
            if (stoi(to_string(board.getFieldInfo(y, x))) >= 1 && stoi(to_string(board.getFieldInfo(y, x))) <= 8) {
                if(font.loadFromFile("../assets/arial.ttf")) {
                    text.setString(to_string(board.getFieldInfo(y, x)));
                    text.setFont(font);
                    text.setFillColor(sf::Color::Blue);
                    text.setCharacterSize(20);
                    text.setPosition(squares[y][x].getPosition().x + 10, squares[y][x].getPosition().y + 2.5);
                    squares[y][x].setFillColor(sf::Color(140,140,140));
                    window.draw(squares[y][x]);
                    window.draw(text);
                }
            }
        }
    }
    if(board.getGameState() == FINISHED_WIN) {
        if(font.loadFromFile("../assets/arial.ttf")) {
            textEndgameWin.setFillColor(sf::Color::Green);
            textEndgameWin.setCharacterSize(35);
            textEndgameWin.setPosition(window.getSize().x / 2.f - textEndgameWin.getLocalBounds().width / 2.f, 10);
            for(i=0; i<board.getBoardHeight(); i++) {
                for(j=0; j<board.getBoardWidth(); j++) {
                    if(board.hasMine(j,i) && squares[j][i].getTexture() == nullptr) {
                        if (textureMine.loadFromFile("../assets/mine_whitebg.png")) {
                            squares[j][i].setTexture(&textureMine);
                            window.draw(squares[j][i]);
                        }
                    }
                }
            }
        }
        window.draw(textEndgameWin);
    } else if(board.getGameState() == FINISHED_LOSS) {
        if(font.loadFromFile("../assets/arial.ttf")) {
            textEndgameLost.setFillColor(sf::Color::Red);
            textEndgameLost.setCharacterSize(35);
            textEndgameLost.setPosition(window.getSize().x / 2.f - textEndgameLost.getLocalBounds().width / 2.f, 10);
            for(i=0; i<board.getBoardHeight(); i++) {
                for(j=0; j<board.getBoardWidth(); j++) {
                    if(board.hasMine(j,i) && squares[j][i].getTexture() == nullptr) {
                        if (textureMine.loadFromFile("../assets/mine_whitebg.png")) {
                            squares[j][i].setTexture(&textureMine);
                            window.draw(squares[j][i]);
                        }
                    }
                }
            }
        }
        window.draw(textEndgameLost);
    }
}