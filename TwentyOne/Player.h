#pragma once
#include "CardDeck.h"

class Player {
public:
    virtual void TakeCard(const Card& NewCard) = 0;
    virtual void Pass() = 0;
    virtual void Move(CardDeck& Deck) = 0;

    virtual void showCards() = 0;

    virtual int GetLife() = 0;
    virtual int GetBid() = 0;
    virtual int GetCardSum() = 0;

    virtual void SetBid(int newBid) = 0;
    virtual void SetLife(int newAlive) = 0;
    virtual void SetCardSum(int newCardSum) = 0;

    virtual void ClearArray() = 0;
};

class YourPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;
    int CardSum = 0;
    int Bid = 1;
    int Life = 10;

    void Pass();

public:
    YourPlayer();
    YourPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard);

    void Move(CardDeck& Deck);

    void showCards();

    int GetCardSum();

    int GetLife();

    int GetBid();

    void SetLife(int newLife);

    void SetBid(int newBid);

    void SetCardSum(int newCardSum);

    void ClearArray();
};

class EnemyPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;
    int CardSum = 0;
    int Bid = 1;
    int Life = 10;

    void Pass();

public:
    EnemyPlayer();
    EnemyPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard);

    void Move(CardDeck& Deck);

    void showCards();

    int GetCardSum();

    int GetLife();

    int GetBid();

    void SetLife(int newLife);

    void SetBid(int newBid);

    void SetCardSum(int newCardSum);

    void ClearArray();
};
