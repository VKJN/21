#include "EnemyPlayer.h"
#include "Game.h"

EnemyPlayer::EnemyPlayer() {}
EnemyPlayer::EnemyPlayer(const Card& FirstCard, const Card& SecondCard) {
    Array_of_cards.push_back(FirstCard);
    Array_of_cards.push_back(SecondCard);

    CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();

    pathFirstCardTexture = "image/Textures for cards/" + std::to_string(Array_of_cards[0].GetNumber()) + ".jpg";

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

void EnemyPlayer::TakeTrump(const TrumpCard& NewTrump) {
    TrumpInventory.push_back(NewTrump);
}

// Метод для смены активного игрока и повышения счетчика пассов (при пассе)
void EnemyPlayer::Pass(bool& WHOMOVE, int& CounterPass) {
    WHOMOVE = !WHOMOVE;
    CounterPass++;
}


// Ход противника, так как в нем вызываются Pass и TakeCard, нужно передать для них соответствующие параметры
int EnemyPlayer::Move(CardDeck& Deck, bool& WHOMOVE, int& CounterPass, int& CardsInDeck, int& winningNumber, YourPlayer& player) {
    /*
    * I know that this is complete horror, and not code, but I don’t know how to do it differently.
    * Had to add method and field to YourPlayer just for this method. And this switch case looks terrible
    */

    std::this_thread::sleep_for(std::chrono::seconds(random(1, 2)));

    std::vector<int> trumpsId;
    for (auto i : TrumpInventory) {
        trumpsId.push_back(i.getId());
    }

    for (int i = 0; i < trumpsId.size(); i++) {
        switch (trumpsId[i]) {
        case 1:
            if (CardSum < winningNumber && CardSum + 2 <= winningNumber) {
                bool flag = true;
                for (auto i : Array_of_cards) {
                    if (i.GetNumber() == 2) {
                        flag = false;
                    }
                }

                std::vector<Card> buf = player.getArrayOfCard();
                for (int i = 1; i < buf.size(); i++) {
                    if (buf[i].GetNumber() == 2) {
                        flag = false;
                    }
                }

                if (flag) {
                    TrumpsShown.push_back(TrumpInventory[i]);
                    TrumpInventory.erase(TrumpInventory.begin() + i);
                    CounterPass = 0;
                    return 1;
                }
            }
            break;

        case 2:
            if (CardSum < winningNumber && CardSum + 3 <= winningNumber) {
                bool flag = true;
                for (auto i : Array_of_cards) {
                    if (i.GetNumber() == 3) {
                        flag = false;
                    }
                }

                std::vector<Card> buf = player.getArrayOfCard();
                for (int i = 1; i < buf.size(); i++) {
                    if (buf[i].GetNumber() == 3) {
                        flag = false;
                    }
                }

                if (flag) {
                    TrumpsShown.push_back(TrumpInventory[i]);
                    TrumpInventory.erase(TrumpInventory.begin() + i);
                    CounterPass = 0;
                    return 1;
                }
            }
            break;

        case 3:
            if (CardSum < winningNumber && CardSum + 4 <= winningNumber) {
                bool flag = true;
                for (auto i : Array_of_cards) {
                    if (i.GetNumber() == 4) {
                        flag = false;
                    }
                }

                std::vector<Card> buf = player.getArrayOfCard();
                for (int i = 1; i < buf.size(); i++) {
                    if (buf[i].GetNumber() == 4) {
                        flag = false;
                    }
                }

                if (flag) {
                    TrumpsShown.push_back(TrumpInventory[i]);
                    TrumpInventory.erase(TrumpInventory.begin() + i);
                    CounterPass = 0;
                    return 1;
                }
            }
            break;

        case 4:
            if (CardSum < winningNumber && CardSum + 5 <= winningNumber) {
                bool flag = true;
                for (auto i : Array_of_cards) {
                    if (i.GetNumber() == 5) {
                        flag = false;
                    }
                }

                std::vector<Card> buf = player.getArrayOfCard();
                for (int i = 1; i < buf.size(); i++) {
                    if (buf[i].GetNumber() == 5) {
                        flag = false;
                    }
                }

                if (flag) {
                    TrumpsShown.push_back(TrumpInventory[i]);
                    TrumpInventory.erase(TrumpInventory.begin() + i);
                    CounterPass = 0;
                    return 1;
                }
            }
            break;

        case 5:
            if (CardSum < winningNumber && CardSum + 6 <= winningNumber) {
                bool flag = true;
                for (auto i : Array_of_cards) {
                    if (i.GetNumber() == 6) {
                        flag = false;
                    }
                }

                std::vector<Card> buf = player.getArrayOfCard();
                for (int i = 1; i < buf.size(); i++) {
                    if (buf[i].GetNumber() == 6) {
                        flag = false;
                    }
                }

                if (flag) {
                    TrumpsShown.push_back(TrumpInventory[i]);
                    TrumpInventory.erase(TrumpInventory.begin() + i);
                    CounterPass = 0;
                    return 1;
                }
            }
            break;

        case 6:
            if (CardSum < winningNumber && CardSum + 7 <= winningNumber) {
                bool flag = true;
                for (auto i : Array_of_cards) {
                    if (i.GetNumber() == 7) {
                        flag = false;
                    }
                }

                std::vector<Card> buf = player.getArrayOfCard();
                for (int i = 1; i < buf.size(); i++) {
                    if (buf[i].GetNumber() == 7) {
                        flag = false;
                    }
                }

                if (flag) {
                    TrumpsShown.push_back(TrumpInventory[i]);
                    TrumpInventory.erase(TrumpInventory.begin() + i);
                    CounterPass = 0;
                    return 1;
                }
            }
            break;

        case 7:
            if ((CardSum < player.GetCardSum() - player.GetFirstCardNumber() && player.GetCardSum() - player.GetFirstCardNumber() < winningNumber) ||
                (CardSum > winningNumber && CardSum > player.GetCardSum() - player.GetFirstCardNumber()) && Bet > 0) 
            {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 8:
            if (player.GetCardSum() - player.GetFirstCardNumber() > CardSum && player.GetCardSum() - player.GetFirstCardNumber() < winningNumber) {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 9:
            if (CardSum > winningNumber) {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 10:
            if ((CardSum < winningNumber && winningNumber - CardSum > winningNumber - CardSum - Array_of_cards.back().GetNumber() + player.GetLastCardNumber() && 
                winningNumber - CardSum - Array_of_cards.back().GetNumber() + player.GetLastCardNumber() >= 0) || 
                (CardSum > winningNumber && winningNumber - CardSum < winningNumber - CardSum - Array_of_cards.back().GetNumber() + player.GetLastCardNumber()))
            {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 11:
            if (CardSum < player.GetCardSum() - player.GetFirstCardNumber() && player.GetCardSum() - player.GetFirstCardNumber() < winningNumber && CardSum >= 10
                && winningNumber > 17) 
            {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 12:
            if (CardSum > winningNumber && winningNumber < 24 && CardSum > player.GetCardSum() - player.GetFirstCardNumber() && CardSum <= 24) {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 13:
            if (CardSum > winningNumber && winningNumber < 27 && CardSum > player.GetCardSum() - player.GetFirstCardNumber() && CardSum <= 27){
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 14:
            if ((CardSum > player.GetCardSum() - player.GetFirstCardNumber() && CardSum <= winningNumber) ||
                (CardSum > winningNumber && CardSum < player.GetCardSum() - player.GetFirstCardNumber()))
            {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;

        case 15:
            if ((CardSum > player.GetCardSum() - player.GetFirstCardNumber() && CardSum <= winningNumber) ||
                (CardSum > winningNumber && CardSum < player.GetCardSum() - player.GetFirstCardNumber()))
            {
                TrumpsShown.push_back(TrumpInventory[i]);
                TrumpInventory.erase(TrumpInventory.begin() + i);
                CounterPass = 0;
                return 1;
            }
            break;
        }
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /*
    * opponent's normal move
    */
    if (CardSum < winningNumber - 4) {
        TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter()), CardsInDeck));
        CounterPass = 0;
        WHOMOVE = !WHOMOVE;
        return 0;
    }

    else {
        Pass(WHOMOVE, CounterPass);
        return -1;
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

    // Прототип
    for (auto i : TrumpsShown) {
        i.setScale(-1, -1);
        i.setTextureCardPosition(cardPosX, cardPosY + 130);
        i.Show(window);
        cardPosX += 140;
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

int EnemyPlayer::GetBet() {
    return Bet;
}

void EnemyPlayer::SetLife(int newLife) {
    this->Life = newLife;
}

void EnemyPlayer::SetCardSum(int newCardSum) {
    this->CardSum = newCardSum;
}

void EnemyPlayer::SetBet(int newBet) {
    this->Bet = newBet;
}

void EnemyPlayer::ClearArray() {
    Array_of_cards.clear();
    TrumpsShown.clear();
}

void EnemyPlayer::ClearInventory() {
    TrumpInventory.clear();
}

void EnemyPlayer::ChangeFirstCardTexture() {
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
void EnemyPlayer::ChangeLifeTexture(int index) {
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

Card EnemyPlayer::removeLastCard() {
    Card last = Array_of_cards.back();
    Array_of_cards.pop_back();
    return last;
}

std::vector<TrumpCard>& EnemyPlayer::getTrumpsShown() {
    return TrumpsShown;
}