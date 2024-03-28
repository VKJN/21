#pragma once
#include "Player.h"
#include "YourPlayer.h"

class EnemyPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;           //������� ���� � ������
    std::vector<TrumpCard> TrumpInventory; // ������, ������� �� ������������
    std::vector<TrumpCard> TrumpsShown;     // �� ������, ������� ��������� ����������� � ������ (������������ ��� �������������)
    std::vector<sf::Sprite> Array_of_Lifes;

    int CardSum = 0; // ����� ����
    int Bet = 1; // ������ (������� ����� ���������� ������ �� ��������)
    int Life = 5; // ���-�� ������

    sf::Texture newLifeTexture;   //�������� ��� ������ (������� ������ � ������)
    sf::Texture textureLife;

    std::string pathFirstCardTexture; // ���� � �������� ������ ����� (�����, ��� ��� ��� ���� ����� �������, � ����� ����� �� �������)

    // 800 = 42% �� 1920; 300 = 28% �� 1080
    int cardPosX = WIDTH * 0.42, cardPosY = HEIGHT * 0.28; // ������� 1 �����

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