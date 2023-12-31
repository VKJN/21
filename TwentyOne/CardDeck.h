#pragma once

class Card {
private:
    int number;
    sf::Texture textureCard;
    sf::Sprite spriteCard;
public:
    Card(int value, sf::Texture& texture_card);

    Card(const Card& copy);

    int GetNumber() const;

    void Show(sf::RenderWindow& window);

    void setTextureCardPosition(int posX, int posY);

    void setScale(int x, int y);

    void changeTexture(sf::Texture newTexture);
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

    void show(sf::RenderWindow& window);
};

void AddInDeck(CardDeck& deck, int& MaxCards);