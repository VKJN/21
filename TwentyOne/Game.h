#pragma once
#include "YourPlayer.h"
#include "EnemyPlayer.h"
#include "CardDeck.h"
#include "TrumpCardDeck.h"

class Game {
private:
    sf::RenderWindow& window;
    sf::RectangleShape background;

    YourPlayer player;
    EnemyPlayer enemy;
    CardDeck deck;
    TrumpCardDeck trumpDeck;

    bool WHOMOVE; // true - твой ход, false - ход противника
    int CounterPass; // Если 2 - закрытые карты открываются
    int CardsInDeck;
    int CardsInTrumpDeck = 31;
    int winningNumber;

    sf::Font font;
    sf::Text yourCloseCard, yourCardSum, enemyCardSum, text, yourBet, enemyBet;

    bool visible = false; // Показ козырей
    sf::RectangleShape windowTrump;

    int yourMove = -1;

    std::string replicas[10] = { "New round", "Your move", "Enemy move", "Draw", "You win", "You lose", "You lose in game" , 
        "You win in game", "Do you want to play again? Y/N", ""};

    std::vector<sf::Text> textReplicas;

    void Round();

    int CheckWinner();

    void RoundResult(int result);

    void RestartRound();

    void addText();

    void whatTrumpCard(std::vector<TrumpCard>& trumps, Player& who);

    void processEvents();
    void update();
    void render(int trigger, sf::Text textToRender);

public:
    Game(CardDeck& deck, int CardsInDeck, sf::RenderWindow & window_, sf::RectangleShape background_);

    void Play();

    int AfterThePlay();
};