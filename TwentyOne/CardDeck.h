#pragma once

class Card {
private:
    int number;
public:
    Card(int value);

    Card(const Card& copy);

    int GetNumber() const;

    void Show();
};

class CardDeck {
private:
    std::vector<Card> deck;
    int CardCounter = 0;
public:
    void AddCard(const Card& NewCardInDeck);

    Card RemoveCard(int index, int& MaxCards);

    int GetCardCounter();

    void SetCardCounter(int newCardCounter);

    void ClearDeck();
};

void AddInDeck(CardDeck& deck, int& MaxCards);