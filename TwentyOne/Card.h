#pragma once
#include "Header.h"

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