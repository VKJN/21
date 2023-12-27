#include "Header.h"
#include "CardDeck.h"

// Методы класса Card

Card::Card(int value) {
    this->number = value;
}

Card::Card(const Card& copy) {
    this->number = copy.number;
}

int Card::GetNumber() const {
    return number;
}

void Card::Show() {
    std::cout << number << " ";
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

// Просто функция, по заполнению колоды
void AddInDeck(CardDeck& deck, int& MaxCards) {
    for (int i = 1; i < MaxCards + 1; i++) {
        deck.AddCard(Card(i));
    }
}