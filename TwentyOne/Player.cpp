#include "Header.h"
#include "Player.h"

// ������ ������ YourPlayer

YourPlayer::YourPlayer() {}
YourPlayer::YourPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();
}

// ����� ��� ���������� � ���� �����, ���� ����� ������� ���� �� ���� ����������� �����
void YourPlayer::TakeCard(const Card& NewCard, int& winningNumber) {
    if (CardSum < winningNumber) {
        Array_of_cards.push_back(NewCard);

        CardSum += NewCard.GetNumber();
    }
    else {
        throw "You can�t take the card while you have too much";
    }
}


// ����� ��� ����� ��������� ������ � ��������� �������� ������ (��� ����)
void YourPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}


// ��� ������, ��� ��� � ��� ���������� Pass � TakeCard, ����� �������� ��� ��� ��������������� ���������
void YourPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber) {
    std::cout << "Your move: " << std::endl;
    int key;
    key = _getch();
    switch (key) {
    case Napravlenie::Two:
        try {
            TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), MaxCards), winningNumber);
            CounterPass = 0;
            WHOMOVE = !WHOMOVE;
        }
        catch (const char* error_message) {
            std::cout << error_message << std::endl;
        }
        break;
    case Napravlenie::Three:
        Pass(WHOMOVE, CounterPass);
        break;
    }
}

void YourPlayer::showCards(sf::RenderWindow& window) {
    for (auto i : Array_of_cards) {
        i.Show(window);
    }
}

int YourPlayer::GetCardSum() {
    return CardSum;
}

int YourPlayer::GetLife() {
    return Life;
}

int YourPlayer::GetBid() {
    return Bid;
}

void YourPlayer::SetLife(int newLife) {
    this->Life = newLife;
}

void YourPlayer::SetBid(int newBid) {
    this->Bid = newBid;
}

void YourPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void YourPlayer::ClearArray() {
    Array_of_cards.clear();
}

// ������ ������ EnemyPlayer

EnemyPlayer::EnemyPlayer() {}
EnemyPlayer::EnemyPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);
    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();
}

void EnemyPlayer::TakeCard(const Card& NewCard, int& winningNumber) {
    Array_of_cards.push_back(NewCard);
    CardSum += NewCard.GetNumber();
}

void EnemyPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}

void EnemyPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber) {
    if (CardSum < 17) {
        TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), MaxCards), winningNumber);
        CounterPass = 0;
        WHOMOVE = !WHOMOVE;
    }
    else {
        Pass(WHOMOVE, CounterPass);
    }
}

void EnemyPlayer::showCards(sf::RenderWindow& window) {
    for (auto i : Array_of_cards) {
        i.Show(window);
    }
}

int EnemyPlayer::GetCardSum() {
    return CardSum;
}

int EnemyPlayer::GetLife() {
    return Life;
}

int EnemyPlayer::GetBid() {
    return Bid;
}

void EnemyPlayer::SetLife(int newLife) {
    this->Life = newLife;
}

void EnemyPlayer::SetBid(int newBid) {
    this->Bid = newBid;
}

void EnemyPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void EnemyPlayer::ClearArray() {
    Array_of_cards.clear();
}