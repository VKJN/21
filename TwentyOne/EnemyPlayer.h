#pragma once
#include "Player.h"
#include "YourPlayer.h"

class EnemyPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;           //¬екторы карт и жизней
    std::vector<TrumpCard> TrumpInventory; //  озыри, которые не отображаютс€
    std::vector<TrumpCard> TrumpsShown;     // “е козыри, которые противник использовал в раунде (отображаютс€ при использовании)
    std::vector<sf::Sprite> Array_of_Lifes;

    int CardSum = 0; // —умма карт
    int Bet = 1; // —тавка (сколько будет отниматьс€ жизней за проигрыш)
    int Life = 5; //  ол-во жизней

    sf::Texture newLifeTexture;   //“екстуры дл€ жизней (красное сердце и пустое)
    sf::Texture textureLife;

    std::string pathFirstCardTexture; // ѕуть к текстуре первой карты (нужен, так как при игре карта закрыта, а потом нужно ее открыть)

    // 800 = 42% от 1920; 300 = 28% от 1080
    int cardPosX = WIDTH * 0.42, cardPosY = HEIGHT * 0.28; // ѕозици€ 1 карты

    void Pass(bool& WHOMOVE, int& CounterPass);

public:
    EnemyPlayer();
    EnemyPlayer(const Card& FirstCard, const Card& SecondCard);

    void TakeCard(const Card& NewCard);
    void TakeTrump(const TrumpCard& NewTrump);

    int Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber, YourPlayer& player);

    void showCards(sf::RenderWindow& window);
    void showLifes(sf::RenderWindow& window);

    int GetCardSum();
    int GetLife();
    int GetBet();

    void SetLife(int newLife);
    void SetCardSum(int newCardSum);
    void SetBet(int newBet);

    void ClearArray();
    void ClearInventory();

    void ChangeFirstCardTexture();
    void ChangeLifeTexture(int index);

    int GetFirstCardNumber();

    void lifeSpriteSetup();

    Card removeLastCard();

    std::vector<TrumpCard>& getTrumpsShown();
};