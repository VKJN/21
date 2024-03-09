#pragma once
#include "CardDeck.h"
#include "Config.h"

class Player {
public:
    virtual void TakeCard(const Card& NewCard) = 0;
    virtual void Pass(bool& WHOMOVE, int& CounterPass) = 0;
    virtual void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber) = 0;

    virtual void showCards(sf::RenderWindow& window) = 0;
    virtual void showLifes(sf::RenderWindow& window) = 0;

    virtual int GetLife() = 0;
    virtual int GetBid() = 0;
    virtual int GetCardSum() = 0;
    virtual int GetFirstCardNumber() = 0;

    virtual void SetLife(int newAlive) = 0;
    virtual void SetCardSum(int newCardSum) = 0;

    virtual void ClearArray() = 0;

    virtual void ChangeFirstCardTexture() = 0;
    virtual void ChangeLifeTexture(int index) = 0;
    virtual void lifeSpriteSetup() = 0;
};