#include "YourPlayer.h"

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

void YourPlayer::TakeTrump(const TrumpCard& NewTrump) {
    TrumpInventory.push_back(NewTrump);
}


// Метод для смены активного игрока и повышения счетчика пассов
void YourPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}


// Ход игрока, так как в нем вызываются Pass и TakeCard, нужно передать для них соответствующие параметры
void YourPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& CardsInDeck, int& winningNumber) {
    if (CardSum <= winningNumber) {
        TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), CardsInDeck));
        CounterPass = 0;
        WHOMOVE = !WHOMOVE;
    }

    else {
        throw "You can't take the card while you have too much";
    }
}


void YourPlayer::showCards(sf::RenderWindow& window) {
    for (auto i : Array_of_cards) {
        i.setTextureCardPosition(cardPosX, cardPosY);
        i.Show(window);
        cardPosX += 170;
    }
    cardPosX = WIDTH * 0.34;

    for (auto i : TrumpsShown) {
        i.setTextureCardPosition(cardPosX, cardPosY - 130);
        i.Show(window);
        cardPosX += 140;
    }
    cardPosX = WIDTH * 0.34;
}

void YourPlayer::showLifes(sf::RenderWindow& window) {
    for (auto i : Array_of_Lifes) {
        window.draw(i);
    }
}

void YourPlayer::showTrumpInventory(sf::RenderWindow& window) {
    int x = 980, y = 50;
    for (int i = 0; i < TrumpInventory.size(); i++) {
        if (i % 5 == 0 && i != 0) {
            y += 170;
            x = 980;
        }
        TrumpInventory[i].setTextureCardPosition(x, y);
        TrumpInventory[i].Show(window);
        x += 170;
    }
}

int YourPlayer::GetCardSum() {
    return CardSum;
}

int YourPlayer::GetLife() {
    return Life;
}

int YourPlayer::GetBet() {
    return Bet;
}

void YourPlayer::SetLife(int newLife) {
    this->Life = newLife;
}

void YourPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void YourPlayer::SetBet(int newBet) {
    this->Bet = newBet;
}

void YourPlayer::ClearArray() {
    Array_of_cards.clear();
    TrumpsShown.clear();
}

void YourPlayer::ClearInventory() {
    TrumpInventory.clear();
}

void YourPlayer::ChangeFirstCardTexture() {
    sf::Texture newTexture;

    if (pathFirstCardTexture == "image/Textures for cards/back of the card.jpg") {
        pathFirstCardTexture = "image/Textures for cards/" + std::to_string(Array_of_cards[0].GetNumber()) + ".jpg";
        if (!newTexture.loadFromFile(pathFirstCardTexture)) {}
    }
    else {
        pathFirstCardTexture = "image/Textures for cards/back of the card.jpg";
        if (!newTexture.loadFromFile(pathFirstCardTexture)) {}
    }
    Array_of_cards[0].changeTexture(newTexture);
}


// Смена текстуры жизни на пустую и наоборот
void YourPlayer::ChangeLifeTexture(int index) {
    if (index == 1) { 
        for (int i = 5; i > Life; i--) {
            Array_of_Lifes[5 - i].setTexture(newLifeTexture);
        }
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

bool YourPlayer::handleMouseClick(const sf::Vector2i& mousePosition) {
    bool result = false;
    int index = 0;

    for (int i = 0; i < TrumpInventory.size(); i++) {
        if (TrumpInventory[i].getPosition().contains(float(mousePosition.x), float(mousePosition.y))) {
            TrumpsShown.push_back(TrumpInventory[i]);
            TrumpInventory.erase(TrumpInventory.begin() + i);
            result = true;
        }
    }

    for (int i = 0; i < TrumpInventory.size(); i++) {
        TrumpInventory[i].setTexture(); // Заново ставить текстуры, так как иначе ужас будет
    }

    return result;
}

std::vector<TrumpCard>& YourPlayer::getTrumpsShown() {
    return TrumpsShown;
}

Card YourPlayer::removeLastCard() {
    Card last = Array_of_cards.back();
    Array_of_cards.pop_back();
    return last;
}

std::vector<Card> YourPlayer::getArrayOfCard() {
    return Array_of_cards;
}

int YourPlayer::GetFirstCardNumber() {
    return Array_of_cards[0].GetNumber();
}

int YourPlayer::GetLastCardNumber() {
    return Array_of_cards.back().GetNumber();
}
