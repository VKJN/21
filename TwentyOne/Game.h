#pragma once
#include "Player.h"
#include "CardDeck.h"

class Game {
private:
    YourPlayer player;
    EnemyPlayer enemy;
    CardDeck deck;
public:
    Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck);

    void Play();

    void Round();

    int CheckWinner();

    void RoundResult(int result);

    void RestartRound();
};