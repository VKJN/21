#pragma once
#include "CardDeck.h"
#include "TrumpCardDeck.h"
#include "Config.h"

class Player {
public:
    virtual void TakeCard(const Card& NewCard) = 0;
    virtual void TakeTrump(const TrumpCard& NewTrump) = 0;
    virtual void Pass(bool& WHOMOVE, int& CounterPass) = 0;

    virtual void showCards(sf::RenderWindow& window) = 0;
    virtual void showLifes(sf::RenderWindow& window) = 0;

    virtual int GetLife() = 0;
    virtual int GetBet() = 0;
    virtual int GetCardSum() = 0;
    virtual int GetFirstCardNumber() = 0;

    virtual void SetLife(int newAlive) = 0;
    virtual void SetCardSum(int newCardSum) = 0;
    virtual void SetBet(int newBet) = 0;

    virtual void ClearArray() = 0;
    virtual void ClearInventory() = 0;

    virtual void ChangeFirstCardTexture() = 0;
    virtual void ChangeLifeTexture(int index) = 0;
    virtual void lifeSpriteSetup() = 0;

    virtual Card removeLastCard() = 0;

    virtual std::vector<TrumpCard>& getTrumpsShown() = 0;
};