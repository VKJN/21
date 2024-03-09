#pragma once
#include "Player.h"

class EnemyPlayer : public Player {
private:
    std::vector<Card> Array_of_cards;           //������� ���� � ������ (�������� ������)
    std::vector<sf::Sprite> Array_of_Lifes;
    int CardSum = 0; // ����� ����
    int Bid = 1; // ������ (������� ����� ���������� ������ �� ��������)
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

    void Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber);

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