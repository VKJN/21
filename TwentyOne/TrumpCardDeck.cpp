#include "TrumpCardDeck.h"

void TrumpCardDeck::AddCard(const TrumpCard& NewCardInDeck) {
	deck.push_back(NewCardInDeck);
}

TrumpCard TrumpCardDeck::RemoveCard(int index, int& CardsInDeck) {
	index--; // -1, потому что мы начинаем считать с 1
	TrumpCard CopyCard = deck[index];
	deck.erase(deck.begin() + index);

	CardsInDeck--;
	return CopyCard;
}

int TrumpCardDeck::GetCardCounter() {
	if (deck.size() > 0) {
		return deck.size();
	}
}

void TrumpCardDeck::ClearDeck() {
	deck.clear();
}

void AddInDeck(TrumpCardDeck& deck, int& CardsInDeck) {
	sf::Texture texture_card;
	std::string cardTexturePath = "";

	for (int i = 0, id = 0; i < CardsInDeck + 1; i++) {
		if (i < 6) {
			cardTexturePath = "image/Textures for trump cards/take" + std::to_string(i + 2) + ".jpg";
			id = i + 1;
		}

		else if (i > 5 && i < 10) {
			cardTexturePath = "image/Textures for trump cards/shield.jpg";
			id = 7;
		}

		else if (i > 9 && i < 14) {
			cardTexturePath = "image/Textures for trump cards/remove.jpg";
			id = 8;
		}

		else if (i > 13 && i < 19) {
			cardTexturePath = "image/Textures for trump cards/return.jpg";
			id = 9;
		}

		else if (i > 18 && i < 23) {
			cardTexturePath = "image/Textures for trump cards/exchange.jpg";
			id = 10;
		}

		else if (i == 23) {
			cardTexturePath = "image/Textures for trump cards/go for 17.jpg";
			id = 11;
		}

		else if (i == 24) {
			cardTexturePath = "image/Textures for trump cards/go for 24.jpg";
			id = 12;
		}

		else if (i == 25) {
			cardTexturePath = "image/Textures for trump cards/go for 27.jpg";
			id = 13;
		}

		else if (i > 25 && i < 28) {
			cardTexturePath = "image/Textures for trump cards/+1.jpg";
			id = 14;
		}

		else {
			cardTexturePath = "image/Textures for trump cards/+2.jpg";
			id = 15;
		}

		if (!texture_card.loadFromFile(cardTexturePath)) {
			std::cout << "Failed to load texture for card " << i << std::endl;
		}

		texture_card.setSmooth(true);
		deck.AddCard(TrumpCard(id, texture_card));
	}
}