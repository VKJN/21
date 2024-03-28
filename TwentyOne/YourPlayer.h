#pragma once
#include "Player.h"

class YourPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;      //Векторы карт и жизней
    std::vector<TrumpCard> TrumpInventory; // Те козыри, которые у тебя в инвентаре (не отображаются, пока не нажмешь 1)
    std::vector<TrumpCard> TrumpsShown;     // Те козыри, которые ты использовал в раунде (отображаются при использовании)
    std::vector<sf::Sprite> Array_of_Lifes;

    int CardSum = 0; // Сумма карт
    int Bet = 1; // Ставка (сколько будет отниматься жизней за проигрыш)
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
    void TakeTrump(const TrumpCard& NewTrump);

    void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber);
    void Pass(bool& WHOMOVE, int& CounterPass);

    void showCards(sf::RenderWindow& window);
    void showLifes(sf::RenderWindow& window);
    void showTrumpInventory(sf::RenderWindow& window);

    int GetCardSum();
    int GetLife();
    int GetBet();
    int GetFirstCardNumber();
    int GetLastCardNumber(); // only for enemyPlayer (method Move)

    void SetLife(int newLife);
    void SetCardSum(int newCardSum);
    void SetBet(int newBet);

    void ClearArray();
    void ClearInventory();

    void ChangeFirstCardTexture();
    void ChangeLifeTexture(int index);

    void lifeSpriteSetup();

    bool handleMouseClick(const sf::Vector2i& mousePosition);

    std::vector<TrumpCard>& getTrumpsShown();

    Card removeLastCard();

    std::vector<Card> getArrayOfCard(); // only for enemyPlayer (method Move)
};