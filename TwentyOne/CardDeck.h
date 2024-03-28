#pragma once
#include "Card.h"

class CardDeck  {
private:
    std::vector<Card> deck;
public:
    void AddCard(const Card& NewCardInDeck);

    Card RemoveCard(int index, int& CardsInDeck);

    int GetCardCounter();

    void ClearDeck();

    int cardSearch(int cardNumber);
};

void AddInDeck(CardDeck& deck, int& CardsInDeck);