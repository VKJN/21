#pragma once
#include "CardDeck.h"

class Player {
public:
    virtual void TakeCard(const Card& NewCard, int& winningNumber) = 0;
    virtual void Pass(bool& WHOMOVE, int& CounterPass) = 0;
    virtual void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, 
        sf::RenderWindow& window, sf::RectangleShape& background, sf::Event& event) = 0;

    virtual void showCards(sf::RenderWindow& window) = 0;

    virtual int GetLife() = 0;
    virtual int GetBid() = 0;
    virtual int GetCardSum() = 0;

    //virtual void SetBid(int newBid) = 0;
    virtual void SetLife(int newAlive) = 0;
    virtual void SetCardSum(int newCardSum) = 0;

    virtual void ClearArray() = 0;
};

class YourPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;
    int CardSum = 0;
    int Bid = 1;
    int Life = 5;

    int cardPosX = 650, cardPosY = 775;

    void Pass(bool& WHOMOVE, int& CounterPass);
public:
    YourPlayer();
    YourPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard, int& winningNumber);

    void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, 
        sf::RenderWindow& window, sf::RectangleShape& background, sf::Event& event);

    void showCards(sf::RenderWindow& window);

    int GetCardSum();

    int GetLife();

    int GetBid();

    void SetLife(int newLife);

    //void SetBid(int newBid);

    void SetCardSum(int newCardSum);

    void ClearArray();
};

class EnemyPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;
    int CardSum = 0;
    int Bid = 1;
    int Life = 5;

    int cardPosX = 800, cardPosY = 300;

    void Pass(bool& WHOMOVE, int& CounterPass);
public:
    EnemyPlayer();
    EnemyPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard, int& winningNumber);

    void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, 
        sf::RenderWindow& window, sf::RectangleShape& background, sf::Event& event);

    void showCards(sf::RenderWindow& window);

    int GetCardSum();

    int GetLife();

    int GetBid();

    void SetLife(int newLife);

    //void SetBid(int newBid);

    void SetCardSum(int newCardSum);

    void ClearArray();

    void ChangeFirstCardTexture(sf::Texture newTexture);
};