#include "Header.h"
#include "Player.h"

// ћетоды класса YourPlayer

YourPlayer::YourPlayer() {}
YourPlayer::YourPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();
}

// ћетод дл€ добавлени€ в руки карты, пока сумма номеров карт не выше выйгрышного числа
void YourPlayer::TakeCard(const Card& NewCard, int& winningNumber) {
    if (CardSum < winningNumber) {
        Array_of_cards.push_back(NewCard);

        CardSum += NewCard.GetNumber();
    }
    else {
        throw "You canТt take the card while you have too much";
    }
}


// ћетод дл€ смены активного игрока и повышени€ счетчика пассов (при пасе)
void YourPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}


// ’од игрока, так как в нем вызываютс€ Pass и TakeCard, нужно передать дл€ них соответствующие параметры
void YourPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& MaxCards, int& winningNumber) {
    std::cout << "Your move: " << std::endl;
    int key;
    key = _getch();
    switch (key) {
    case 2:
        try {
            TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), MaxCards), winningNumber);
            CounterPass = 0;
            WHOMOVE = !WHOMOVE;
        }
        catch (const char* error_message) {
            std::cout << error_message << std::endl;
        }
        break;
    case 3:
        Pass(WHOMOVE, CounterPass);
        break;
    }
}

void YourPlayer::showCards(sf::RenderWindow& window) {
    for (auto i : Array_of_cards) {
        i.setTextureCardPosition(cardPosX, cardPosY);
        i.Show(window);
        cardPosX += 170;
    }
    cardPosX = 650;
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

//void YourPlayer::SetBid(int newBid) {
//    this->Bid = newBid;
//}

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

    sf::Texture newCardTexture;
    newCardTexture.loadFromFile("image/back of the card.jpg");
    ChangeFirstCardTexture(newCardTexture);
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
        i.setScale(-1, -1);
        i.setTextureCardPosition(cardPosX, cardPosY);
        i.Show(window);
        cardPosX += 170;
    }
    cardPosX = 800;
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

//void EnemyPlayer::SetBid(int newBid) {
//    this->Bid = newBid;
//}

void EnemyPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void EnemyPlayer::ClearArray() {
    Array_of_cards.clear();
}

void EnemyPlayer::ChangeFirstCardTexture(sf::Texture newTexture) {
    Array_of_cards[0].changeTexture(newTexture);
}