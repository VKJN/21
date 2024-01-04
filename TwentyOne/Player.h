#pragma once
#include "CardDeck.h"

class Player {
public:
    virtual void TakeCard(const Card& NewCard) = 0;
    virtual void Pass(bool& WHOMOVE, int& CounterPass) = 0;
    virtual void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, 
        sf::RenderWindow& window) = 0;

    virtual void showCards(sf::RenderWindow& window) = 0;
    virtual void showLifes(sf::RenderWindow& window) = 0;

    virtual void ChangeLifeTexture() = 0;
    virtual void lifeSpriteSetup() = 0;

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
    std::vector<Card> Array_of_cards;           //Векторы карт и жизней (спрайтов жизней)
    std::vector<sf::Sprite> Array_of_Lifes;
    int CardSum = 0; // Сумма карт
    int Bid = 1; // Ставка (сколько будет отниматься жизней за проигрыш)
    int Life = 5; // Кол-во жизней

    sf::Texture newLifeTexture;   //Текстуры для жизней (красное сердце и пустое)
    sf::Texture textureLife;

    int cardPosX = 650, cardPosY = 775; // Позиция 1 карты

    void Pass(bool& WHOMOVE, int& CounterPass);

    void lifeSpriteSetup();
public:
    YourPlayer();
    YourPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard);

    void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, 
        sf::RenderWindow& window);

    void showCards(sf::RenderWindow& window);

    void showLifes(sf::RenderWindow& window);

    int GetCardSum();

    int GetLife();

    int GetBid();

    void SetLife(int newLife);

    //void SetBid(int newBid);

    void SetCardSum(int newCardSum);

    void ClearArray();

    void ChangeLifeTexture();
};

class EnemyPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;           //Векторы карт и жизней (спрайтов жизней)
    std::vector<sf::Sprite> Array_of_Lifes;
    int CardSum = 0; // Сумма карт
    int Bid = 1; // Ставка (сколько будет отниматься жизней за проигрыш)
    int Life = 5; // Кол-во жизней

    sf::Texture newLifeTexture;   //Текстуры для жизней (красное сердце и пустое)
    sf::Texture textureLife;

    std::string pathFirstCardTexture; // Путь к текстуре первой карты (нужен, так как при игре карта закрыта, а потом нужно ее открыть)

    int cardPosX = 800, cardPosY = 300; // Позиция 1 карты

    void Pass(bool& WHOMOVE, int& CounterPass);

    void lifeSpriteSetup();
public:
    EnemyPlayer();
    EnemyPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard);

    void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, 
        sf::RenderWindow& window);

    void showCards(sf::RenderWindow& window);

    void showLifes(sf::RenderWindow& window);

    int GetCardSum();

    int GetLife();

    int GetBid();

    void SetLife(int newLife);

    //void SetBid(int newBid);

    void SetCardSum(int newCardSum);

    void ClearArray();

    void ChangeFirstCardTexture();

    void ChangeLifeTexture();
};