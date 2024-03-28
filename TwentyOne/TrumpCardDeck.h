#pragma once
#include "TrumpCard.h"

class TrumpCardDeck {
private:
    std::vector <TrumpCard> deck;
public:
    void AddCard(const TrumpCard& NewCardInDeck);

    TrumpCard RemoveCard(int index, int& CardsInDeck);

    int GetCardCounter();

    void ClearDeck();
};

void AddInDeck(TrumpCardDeck& deck, int& CardsInDeck);