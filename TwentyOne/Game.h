#pragma once
#include "Player.h"
#include "CardDeck.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::RectangleShape background;

    YourPlayer player;
    EnemyPlayer enemy;
    CardDeck deck;

    bool WHOMOVE; // true - your move, false - enemy move
    int CounterPass; // if 2 - opening of closed cards
    int MaxCards;
    int winningNumber;

    sf::Font font;
    sf::Text text;
    int textPosX, textPosY;

    void Round();

    int CheckWinner();

    void RoundResult(int result);

    void RestartRound();

    void AddText(std::string newText, sf::Color newColor, int size);
public:
    Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck, int MaxCards, 
        sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& background);

    void Play();
};