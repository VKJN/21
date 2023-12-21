#include "Header.h"
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

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"Twenty One", sf::Style::Fullscreen);

    sf::RectangleShape background(sf::Vector2f(150, 225));

    sf::Texture texture;
    if (!texture.loadFromFile("image/1.jpg"))
    {
        // error...
    }
    background.setPosition(0, 0);
    background.setTexture(&texture);

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(background);
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