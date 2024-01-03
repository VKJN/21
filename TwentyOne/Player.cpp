#include "Header.h"
#include "Player.h"

// ћетоды класса YourPlayer

YourPlayer::YourPlayer() {}
YourPlayer::YourPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();

    lifeSpriteSetup();
}

// ћетод дл€ добавлени€ в руки карты, пока сумма номеров карт не выше выйгрышного числа
void YourPlayer::TakeCard(const Card& NewCard) {
    Array_of_cards.push_back(NewCard);
    CardSum += NewCard.GetNumber();
}


// ћетод дл€ смены активного игрока и повышени€ счетчика пассов (при пасе)
void YourPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}


// ’од игрока, так как в нем вызываютс€ Pass и TakeCard, нужно передать дл€ них соответствующие параметры
void YourPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& CardsInDeck, int& winningNumber,
    sf::RenderWindow& window) {

    std::cout << "Your move: " << "\n";
    bool result = false;

    while (!result) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            try {
                if (CardSum <= winningNumber) {
                    TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), CardsInDeck));
                    CounterPass = 0;
                    WHOMOVE = !WHOMOVE;
                    result = true;
                }
                else {
                    throw "You canТt take the card while you have too much";
                }
            }
            catch (const char* error_message) {
                std::cout << error_message << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            Pass(WHOMOVE, CounterPass);
            result = true;
        }
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            std::exit(0);
        }*/
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

void YourPlayer::showLifes(sf::RenderWindow& window) {
    for (auto i : Array_of_Lifes) {
        window.draw(i);
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

//void YourPlayer::SetBid(int newBid) {
//    this->Bid = newBid;
//}

void YourPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void YourPlayer::ClearArray() {
    Array_of_cards.clear();
}

void YourPlayer::ChangeLifeTexture() {
    if (!newLifeTexture.loadFromFile("image/empty life.png")) {}
    Array_of_Lifes[5 - Life].setTexture(newLifeTexture);
}

void YourPlayer::lifeSpriteSetup() {
    if (!textureLife.loadFromFile("image/full life.png")) {}

    sf::Sprite spriteLife;
    spriteLife.setTexture(textureLife);

    for (int i = 0, posX = 80, posY = 650; i < 5; i++, posY += 60) {
        spriteLife.setPosition(posX, posY);
        Array_of_Lifes.push_back(spriteLife);
    }
}

// ћетоды класса EnemyPlayer

EnemyPlayer::EnemyPlayer() {}
EnemyPlayer::EnemyPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();

    ChangeFirstCardTexture();

    lifeSpriteSetup();
}

void EnemyPlayer::TakeCard(const Card& NewCard) {
    Array_of_cards.push_back(NewCard);
    CardSum += NewCard.GetNumber();

    if (Array_of_cards.size() == 1) {
        ChangeFirstCardTexture();
    }
}

void EnemyPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}

void EnemyPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& CardsInDeck, int& winningNumber,
    sf::RenderWindow& window) {

    std::cout << "Enemy move: " << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(random(2, 4)));

    if (CardSum < 17) {
        TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), CardsInDeck));
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

void EnemyPlayer::showLifes(sf::RenderWindow& window) {
    for (auto i : Array_of_Lifes) {
        window.draw(i);
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

//void EnemyPlayer::SetBid(int newBid) {
//    this->Bid = newBid;
//}

void EnemyPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void EnemyPlayer::ClearArray() {
    Array_of_cards.clear();
}

void EnemyPlayer::ChangeFirstCardTexture() {
    sf::Texture newTexture;
    if (!newTexture.loadFromFile("image/back of the card.jpg")) {}

    Array_of_cards[0].changeTexture(newTexture);
}

void EnemyPlayer::ChangeLifeTexture() {
    if (!newLifeTexture.loadFromFile("image/empty life.png")) {}
    Array_of_Lifes[5 - Life].setTexture(newLifeTexture);
}

void EnemyPlayer::lifeSpriteSetup() {
    if (!textureLife.loadFromFile("image/full life.png")) {}

    sf::Sprite spriteLife;
    spriteLife.setTexture(textureLife);

    for (int i = 0, posX = 80, posY = 80; i < 5; i++, posY += 60) {
        spriteLife.setPosition(posX, posY);
        Array_of_Lifes.push_back(spriteLife);
    }
}