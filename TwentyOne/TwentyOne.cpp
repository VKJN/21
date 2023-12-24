#include "Header.h"
#include "GameMenu.h"
#include "Game.h"

//class TrumpCards {
//private:
//
//public:
//
//};
//
//class SpecialCardDeck {
//private:
//    vector<TrumpCards*> deck;
//
//public:
//    void AddCard(TrumpCards* newSpecialCard) {
//        deck.push_back(newSpecialCard);
//    }
//
//    ~SpecialCardDeck() {
//        for (TrumpCards* card : deck) {
//            delete card;
//        }
//        deck.clear();
//    }
//};

const float width = sf::VideoMode::getDesktopMode().width;
const float height = sf::VideoMode::getDesktopMode().height;
const sf::Color menuTextColor(240, 150, 0, 255);
const int tricknessSize = 3;

void initText(sf::Text& text, float posX, float posY, std::string str, int sizeFont, sf::Color menuTextColor) {
    text.setCharacterSize(sizeFont);
    text.setPosition(posX, posY);
    text.setString(str);
    text.setFillColor(menuTextColor);
    text.setOutlineThickness(tricknessSize);
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"Twenty One", sf::Style::Fullscreen);

    sf::RectangleShape background(sf::Vector2f(width, height));

    sf::Texture texture_window;
    if (!texture_window.loadFromFile("image/background.jpg")) {
        // error...
    }
    background.setTexture(&texture_window);

    sf::Font menuFont;
    if (!menuFont.loadFromFile("fonts/ariali.ttf")) {
        // error...
    }

    sf::Text titul;
    titul.setFont(menuFont);
    initText(titul, 600, 50, "Twenty One", 125, menuTextColor);

    std::string nameMenu[4]{ "Play", "Options", "About play", "Exit" };

    GameMenu game(950, 350, 65, 120, nameMenu);
    game.setColorTextMenu(menuTextColor, sf::Color::Red);
    game.AlignMenu();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear();
        window.draw(background);
        window.draw(titul);
        game.draw(window);
        window.display();
    }

    //CardDeck deck;
    //AddInDeck(deck);

    //YourPlayer player(deck.RemoveCard(random(1, MAX_CARDS)), deck.RemoveCard(random(1, MAX_CARDS)));
    //EnemyPlayer enemy(deck.RemoveCard(random(1, MAX_CARDS)), deck.RemoveCard(random(1, MAX_CARDS)));

    //Game game21(player, enemy, deck);

    ////Потом сделать Do While
    //game21.Play();

    /*for (int i = 0;; ++i) {      Для проверки, какая клавиша под каким номером
        if (_kbhit()) {
            int key = _getch();
            cout << key << endl;
            if (key == 0x1B) break;
        }
    }*/

    /*int SecondsPassed = 0;                            Подсчет времени
    auto start = chrono::steady_clock::now();
    while (bal <= 9) {
        auto current_time = chrono::steady_clock::now();
        if (current_time - start >= chrono::seconds(1)) {
            system("cls");
            start = current_time;
            cout << "Time elapsed - " << ++SecondsPassed;
        }
    }*/
    return 0;
}