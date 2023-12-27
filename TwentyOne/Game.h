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

    void Round();

    int CheckWinner();

    void RoundResult(int result);

    void RestartRound();
public:
    Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck, int MaxCards);

    void Play();
};