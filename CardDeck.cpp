#include "Header.h"
#include "CardDeck.h"

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
}

void CardDeck::ClearDeck() {
    deck.clear();
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