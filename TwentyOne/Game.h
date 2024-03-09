#pragma once
#include "YourPlayer.h"
#include "EnemyPlayer.h"
#include "CardDeck.h"

class Game {
private:
    sf::RenderWindow& window;
    sf::RectangleShape background;

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

    std::string replicas[9] = { "New round", "Your move", "Enemy move", "Draw", "You win", "You lose", "You lose in game" , 
        "You win in game", "Do you want to play again? Y/N" };

    void Round();

    int CheckWinner();

    void RoundResult(int result);

    void RestartRound();

    void SetText(std::string newText, sf::Color newColor, int thickness, int size, int trigger);

    void show();

    void processEvents();
    void update();
    void render();
public:
    Game(CardDeck& deck, int CardsInDeck, sf::RenderWindow& window_, sf::RectangleShape background_);

    void Play();

    int AfterThePlay();
};