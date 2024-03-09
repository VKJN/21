#pragma once
#include "Player.h"

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
public:
    YourPlayer();
    YourPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard);

    void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber);

    void Pass(bool& WHOMOVE, int& CounterPass);

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