#include "Header.h"
#include "CardDeck.h"

// Методы класса Card

Card::Card(int value, sf::Texture texture_card) {
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
    //std::cout << number << std::endl;
    std::cout << "Card number: " << number << " Position: (" << spriteCard.getPosition().x << ", " << spriteCard.getPosition().y << ")" << std::endl;
}

void Card::setTextureCardPosition(int posX, int posY) {
    spriteCard.setPosition(posX, posY);
}

// Методы класса CardDeck

void CardDeck::AddCard(const Card& NewCardInDeck) {
    deck.push_back(NewCardInDeck);
    CardCounter++;
}

Card CardDeck::RemoveCard(int index, int& MaxCards) {
    index--; // -1, because we started counting from 1
    Card CopyCard = deck[index];
    deck.erase(deck.begin() + index);

    MaxCards--;
    CardCounter--;
    return CopyCard;
}

int CardDeck::GetCardCounter() {
    if (deck.size() > 0) {
        return CardCounter;
    }
    else {
        throw "Deck of cards is empty";
    }
}

void CardDeck::SetCardCounter(int newCardCounter) {
    this->CardCounter = newCardCounter;
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
    std::cout << "Number of cards on screen: " << CardCounter << std::endl;
}

// Просто функция по заполнению колоды
void AddInDeck(CardDeck& deck, int& MaxCards) {
    sf::Texture texture_card;
    for (int i = 1; i < MaxCards + 1; i++) {
        std::string cardTexturePath = "image/" + std::to_string(i) + ".jpg";

        if (!texture_card.loadFromFile(cardTexturePath)) {
            std::cout << "Failed to load texture for card " << i << std::endl;
        }
        texture_card.setSmooth(true);
        deck.AddCard(Card(i, texture_card));
    }
}