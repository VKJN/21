#pragma once
#include "Player.h"
#include "CardDeck.h"

class Game {
private:
    YourPlayer player;
    EnemyPlayer enemy;
    CardDeck deck;

    bool WHOMOVE; // true - твой ход, false - ход противника
    int CounterPass; // Если 2 - закрытые карты открываются
    int CardsInDeck;
    int winningNumber;

    sf::Font font;
    sf::Text text;
    int textPosX, textPosY;

    void Round(sf::RenderWindow& window, sf::RectangleShape& background);

    int CheckWinner();

    void RoundResult(int result, sf::RenderWindow& window, sf::RectangleShape& background);

    void RestartRound();

    void SetText(std::string newText, sf::Color newColor, int thickness, int size, int trigger);

    void show(sf::RenderWindow& window, sf::RectangleShape& background);
public:
    Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck, int CardsInDeck);

    void Play(sf::RenderWindow& window, sf::RectangleShape& background);

    int AfterThePlay(sf::RenderWindow& window, sf::RectangleShape& background);
};