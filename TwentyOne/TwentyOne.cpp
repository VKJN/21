﻿#include "Header.h"
#include "Config.h"
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
    setlocale(LC_ALL, "rus");

    // Установка фона, шрифта, текста, подготовка меню

    //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Twenty One", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1800, 1000), "Twenty One");

    sf::RectangleShape background(sf::Vector2f(WIDTH, HEIGHT));

    sf::Texture texture_window;
    if (!texture_window.loadFromFile("image/background.jpg")) {
        // error...
    }
    background.setTexture(&texture_window);

    sf::Font menuFont;
    if (!menuFont.loadFromFile("fonts/comici.ttf")) {
        // error...
    }

    sf::Text titul;
    titul.setFont(menuFont);
    initText(titul, 600, 50, "Twenty One", 125, menuTextColor);

    std::vector<std::string> nameMenu{ "Play", "Rules", "Exit" };

    GameMenu Menu(950, 400, 65, 150, nameMenu);
    Menu.setColorTextMenu(menuTextColor);
    Menu.AlignMenu();

    int CardsInDeck = 11;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            Menu.GamePlayMenu(window, background, titul, event);

            CardDeck deck;
            AddInDeck(deck, CardsInDeck);

            YourPlayer player(deck.RemoveCard(random(1, CardsInDeck), CardsInDeck), deck.RemoveCard(random(1, CardsInDeck), CardsInDeck));
            EnemyPlayer enemy(deck.RemoveCard(random(1, CardsInDeck), CardsInDeck), deck.RemoveCard(random(1, CardsInDeck), CardsInDeck));

            Game game21(player, enemy, deck, CardsInDeck, window, event, background);
            game21.Play();

            /*do {
                game21.Play();

            } while (true);*/ 
        }
        /*window.clear();
        window.draw(background);
        window.draw(titul);
        window.display();*/
    }
   
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
}