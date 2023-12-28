#include "Header.h"
#include "CardDeck.h"

// Методы класса Card

Card::Card(int value, sf::Texture& texture_card) {
    this->number = value;
    textureCard.setTexture(&texture_card);
}

Card::Card(const Card& copy, sf::Texture& texture_card) {
    this->number = copy.number;
    this->textureCard.setTexture(&texture_card);
}

int Card::GetNumber() const {
    return number;
}

void Card::Show(sf::RenderWindow& window) {
    window.draw(textureCard);
    std::cout << number << std::endl;
}

void Card::setTextureCardPosition(int posX, int posY) {
    textureCard.setPosition(posX, posY);
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
    int x = 300, y = 300;
    for (int i = 0; i < CardCounter; i++) {
        deck[i].setTextureCardPosition(x, y);
        deck[i].Show(window);
        x += 50;
    }
}

// Просто функция по заполнению колоды
void AddInDeck(CardDeck& deck, int& MaxCards) {
    for (int i = 1; i < MaxCards + 1; i++) {
        sf::Texture texture_card;
        std::string cardTexturePath = "image/" + std::to_string(i) + ".jpg";

        if (!texture_card.loadFromFile(cardTexturePath)) {
            // error...
        }
        deck.AddCard(Card(i, texture_card));
    }
}