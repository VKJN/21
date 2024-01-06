#include "Header.h"
#include "Player.h"

// МЕТОДЫ КЛАССA YourPlayer

YourPlayer::YourPlayer() {}
YourPlayer::YourPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();

    pathFirstCardTexture = "image/" + std::to_string(Array_of_cards[0].GetNumber()) + ".jpg";

    ChangeFirstCardTexture();

    newLifeTexture.loadFromFile("image/empty life.png");
    textureLife.loadFromFile("image/full life.png");

    lifeSpriteSetup();
}

// Метод для добавления в руки карты, пока сумма номеров карт не выше выйгрышного числа
void YourPlayer::TakeCard(const Card& NewCard) {
    Array_of_cards.push_back(NewCard);
    CardSum += NewCard.GetNumber();

    if (Array_of_cards.size() == 1) {
        ChangeFirstCardTexture();
    }
}


// Метод для смены активного игрока и повышения счетчика пассов (при пассе)
void YourPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}


// Ход игрока, так как в нем вызываются Pass и TakeCard, нужно передать для них соответствующие параметры
void YourPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& CardsInDeck, int& winningNumber,
    sf::RenderWindow& window) {

    std::cout << "Your move: " << "\n";
    bool result = false;

    while (!result) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            if (CardSum <= winningNumber) {
                TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), CardsInDeck));
                CounterPass = 0;
                WHOMOVE = !WHOMOVE;
                result = true;
            }
            else {
                throw "You cannot take the card while you have too much";
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            Pass(WHOMOVE, CounterPass);
            result = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            std::exit(0);
        }
    }
}


void YourPlayer::showCards(sf::RenderWindow& window) {
    for (auto i : Array_of_cards) {
        i.setTextureCardPosition(cardPosX, cardPosY);
        i.Show(window);
        cardPosX += 170;
    }
    cardPosX = WIDTH * 0.34;
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

void YourPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void YourPlayer::ClearArray() {
    Array_of_cards.clear();
}

void YourPlayer::ChangeFirstCardTexture() {
    sf::Texture newTexture;

    if (pathFirstCardTexture == "image/back of the card.jpg") {
        pathFirstCardTexture = "image/" + std::to_string(Array_of_cards[0].GetNumber()) + ".jpg";
        if (!newTexture.loadFromFile(pathFirstCardTexture)) {}
    }
    else {
        pathFirstCardTexture = "image/back of the card.jpg";
        if (!newTexture.loadFromFile(pathFirstCardTexture)) {}
    }
    Array_of_cards[0].changeTexture(newTexture);
}


// Смена текстуры жизни на пустую и наоборот
void YourPlayer::ChangeLifeTexture(int index) {
    if (index == 1) {
        Array_of_Lifes[5 - Life].setTexture(newLifeTexture);
    }
    else {
        Array_of_Lifes.clear();
        lifeSpriteSetup();
    }
}


// Метод для установки текстуры и спрайта жизней и добавление спрайта в вектор
void YourPlayer::lifeSpriteSetup() {
    sf::Sprite spriteLife;
    spriteLife.setTexture(textureLife);

    for (int i = 0, posX = 100, posY = HEIGHT * 0.6; i < 5; i++, posY += 60) {  //650 = 60% от 1080
        spriteLife.setPosition(posX, posY);
        Array_of_Lifes.push_back(spriteLife);
    }
}

int YourPlayer::GetFirstCardNumber() {
    return Array_of_cards[0].GetNumber();
}


// МЕТОДЫ КЛАССA EnemyPlayer

EnemyPlayer::EnemyPlayer() {}
EnemyPlayer::EnemyPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();

    pathFirstCardTexture = "image/" + std::to_string(Array_of_cards[0].GetNumber()) + ".jpg";

    ChangeFirstCardTexture();

    newLifeTexture.loadFromFile("image/empty life.png");
    textureLife.loadFromFile("image/full life.png");

    lifeSpriteSetup();
}

void EnemyPlayer::TakeCard(const Card& NewCard) {
    Array_of_cards.push_back(NewCard);
    CardSum += NewCard.GetNumber();

    if (Array_of_cards.size() == 1) {
        ChangeFirstCardTexture();
    }
}


// Метод для смены активного игрока и повышения счетчика пассов (при пассе)
void EnemyPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}


// Ход противника, так как в нем вызываются Pass и TakeCard, нужно передать для них соответствующие параметры
void EnemyPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& CardsInDeck, int& winningNumber,
    sf::RenderWindow& window) {

    std::cout << "Enemy move: " << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(random(1, 3)));

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
    cardPosX = WIDTH * 0.42;
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

void EnemyPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void EnemyPlayer::ClearArray() {
    Array_of_cards.clear();
}

void EnemyPlayer::ChangeFirstCardTexture() {
    sf::Texture newTexture;

    if (pathFirstCardTexture == "image/back of the card.jpg") {
        pathFirstCardTexture = "image/" + std::to_string(Array_of_cards[0].GetNumber()) + ".jpg";
        if (!newTexture.loadFromFile(pathFirstCardTexture)) {}
    }
    else {
        pathFirstCardTexture = "image/back of the card.jpg";
        if (!newTexture.loadFromFile(pathFirstCardTexture)) {}
    }
    Array_of_cards[0].changeTexture(newTexture);
}


// Смена текстуры жизни на пустую и наоборот
void EnemyPlayer::ChangeLifeTexture(int index) {
    if (index == 1) {
        Array_of_Lifes[5 - Life].setTexture(newLifeTexture);
    }
    else {
        Array_of_Lifes.clear();
        lifeSpriteSetup();
    }
}


// Метод для установки текстуры и спрайта жизней и добавление спрайта в вектор
void EnemyPlayer::lifeSpriteSetup() {
    sf::Sprite spriteLife;
    spriteLife.setTexture(textureLife);

    for (int i = 0, posX = 100, posY = 100; i < 5; i++, posY += 60) {
        spriteLife.setPosition(posX, posY);
        Array_of_Lifes.push_back(spriteLife);
    }
}

int EnemyPlayer::GetFirstCardNumber() {
    return Array_of_cards[0].GetNumber();
}