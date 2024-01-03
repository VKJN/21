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
public:
    void AddCard(const Card& NewCardInDeck);

    Card RemoveCard(int index, int& CardsInDeck);

    int GetCardCounter();

    void ClearDeck();

    void show(sf::RenderWindow& window);
};

void AddInDeck(CardDeck& deck, int& CardsInDeck);