#include "Header.h"
#include "Player.h"

// ћетоды класса YourPlayer

YourPlayer::YourPlayer() {}
YourPlayer::YourPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();
}

void YourPlayer::TakeCard(const Card& NewCard) {
    if (CardSum < winningNumber) {
        Array_of_cards.push_back(NewCard);

        CardSum += NewCard.GetNumber();
    }
    else {
        throw "You canТt take the card while you have too much";
    }
}

void YourPlayer::Pass() {
    MOVE = !MOVE;
    CounterPass++;
}

void YourPlayer::Move(CardDeck& Deck) {
    std::cout << "Your move: " << std::endl;
    int key;
    key = _getch();
    switch (key) {
    case Napravlenie::Two:
        try {
            TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter())));
            CounterPass = 0;
            MOVE = !MOVE;
        }
        catch (const char* error_message) {
            std::cout << error_message << std::endl;
        }
        break;
    case Napravlenie::Three:
        Pass();
        break;
    }
}

void YourPlayer::showCards() {
    for (auto i : Array_of_cards) {
        i.Show();
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

// ћетоды класса EnemyPlayer

EnemyPlayer::EnemyPlayer() {}
EnemyPlayer::EnemyPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);
    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();
}

void EnemyPlayer::TakeCard(const Card& NewCard) {
    Array_of_cards.push_back(NewCard);
    CardSum += NewCard.GetNumber();
}

void EnemyPlayer::Pass() {
    MOVE = !MOVE;
    CounterPass++;
}

void EnemyPlayer::Move(CardDeck& Deck) {
    if (CardSum < 17) {
        TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter())));
        CounterPass = 0;
        MOVE = !MOVE;
    }
    else {
        Pass();
    }
}

void EnemyPlayer::showCards() {
    for (auto i : Array_of_cards) {
        i.Show();
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