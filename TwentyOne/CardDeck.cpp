#include "Header.h"
#include "CardDeck.h"

// Методы класса Card

Card::Card(int value, sf::Texture& texture_card) {
    this->number = value;
    this->textureCard = texture_card;
    spriteCard.setTexture(textureCard);
}

Card::Card(const Card& copy) {
    this->number = copy.number;
    this->textureCard = copy.textureCard;
    spriteCard.setTexture(copy.textureCard);
}

int Card::GetNumber() const {
    return number;
}

void Card::Show(sf::RenderWindow& window) {
    window.draw(spriteCard);
}

void Card::setTextureCardPosition(int posX, int posY) {
    spriteCard.setPosition(posX, posY);
}

// Метод, используемый enemy, чтобы его карты были перевернуты
void Card::setScale(int x,int y) {
    spriteCard.setScale(x, y);
}

void Card::changeTexture(sf::Texture newTexture) {
    this->textureCard = newTexture;
    spriteCard.setTexture(textureCard);
}

// Методы класса CardDeck

void CardDeck::AddCard(const Card& NewCardInDeck) {
    deck.push_back(NewCardInDeck);
}

Card CardDeck::RemoveCard(int index, int& CardsInDeck) {
    index--; // -1, потому что мы начинаем считать с 1
    Card CopyCard = deck[index];
    deck.erase(deck.begin() + index);

    CardsInDeck--;
    return CopyCard;
}

int CardDeck::GetCardCounter() {
    if (deck.size() > 0) {
        return deck.size();
    }
    else {
        throw "Deck of cards is empty";
    }
}

void CardDeck::ClearDeck() {
    deck.clear();
}

void CardDeck::show(sf::RenderWindow& window) {
    int x = 100, y = 300;
    for (auto i : deck) {
        i.setTextureCardPosition(x, y);
        i.Show(window);
        x += 155;
    }
}

// Просто функция по заполнению колоды
void AddInDeck(CardDeck& deck, int& CardsInDeck) {
    sf::Texture texture_card;
    for (int i = 1; i < CardsInDeck + 1; i++) {
        std::string cardTexturePath = "image/" + std::to_string(i) + ".jpg";

        if (!texture_card.loadFromFile(cardTexturePath)) {
            std::cout << "Failed to load texture for card " << i << std::endl;
        }
        texture_card.setSmooth(true);
        deck.AddCard(Card(i, texture_card));
    }
}