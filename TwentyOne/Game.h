#pragma once
#include "Player.h"
#include "CardDeck.h"

class Game {
private:
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

    void Round(sf::RenderWindow& window);

    int CheckWinner();

    void RoundResult(int result);

    void RestartRound();

    void AddText(std::string newText, sf::Color newColor, int size, sf::RenderWindow& window);
public:
    Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck, int MaxCards);

    void Play(sf::RenderWindow& window);
};