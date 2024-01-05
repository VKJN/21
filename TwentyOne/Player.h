#pragma once
#include "CardDeck.h"
#include "Config.h"

class Player {
public:
    virtual void TakeCard(const Card& NewCard) = 0;
    virtual void Pass(bool& WHOMOVE, int& CounterPass) = 0;
    virtual void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, sf::RenderWindow& window) = 0;

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

class YourPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;           //Векторы карт и жизней (спрайтов жизней)
    std::vector<sf::Sprite> Array_of_Lifes;
    int CardSum = 0; // Сумма карт
    int Bid = 1; // Ставка (сколько будет отниматься жизней за проигрыш)
    int Life = 5; // Кол-во жизней

    sf::Texture newLifeTexture;   //Текстуры для жизней (красное сердце и пустое)
    sf::Texture textureLife;

    std::string pathFirstCardTexture; // Путь к текстуре первой карты (нужен, так как при игре карта закрыта, а потом нужно ее открыть)

    // 650 = 34% от 1920; 775 = 72% от 1080
    int cardPosX = WIDTH * 0.34, cardPosY = HEIGHT * 0.72; // Позиция 1 карты

    void Pass(bool& WHOMOVE, int& CounterPass);
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

    void SetCardSum(int newCardSum);

    void ClearArray();

    void ChangeFirstCardTexture();

    void ChangeLifeTexture(int index);

    int GetFirstCardNumber();

    void lifeSpriteSetup();
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

    // 800 = 42% от 1920; 300 = 28% от 1080
    int cardPosX = WIDTH * 0.42, cardPosY = HEIGHT * 0.28; // Позиция 1 карты

    void Pass(bool& WHOMOVE, int& CounterPass);
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

    void SetCardSum(int newCardSum);

    void ClearArray();

    void ChangeFirstCardTexture();

    void ChangeLifeTexture(int index);

    int GetFirstCardNumber();

    void lifeSpriteSetup();
};