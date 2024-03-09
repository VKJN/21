#include "Card.h"

Card::Card(int value, sf::Texture& texture_card) {
    this->number = value;
    this->textureCard = texture_card;
    spriteCard.setTexture(textureCard);
}

Card::Card(const Card& copy) {
    this->number = copy.number;
    this->textureCard = copy.textureCard;
    spriteCard.setTexture(copy.textureCard);
}

int Card::GetNumber() const {
    return number;
}

void Card::Show(sf::RenderWindow& window) {
    window.draw(spriteCard);
}

void Card::setTextureCardPosition(int posX, int posY) {
    spriteCard.setPosition(posX, posY);
}

// Метод, используемый enemy, чтобы его карты были перевернуты
void Card::setScale(int x, int y) {
    spriteCard.setScale(x, y);
}

void Card::changeTexture(sf::Texture newTexture) {
    this->textureCard = newTexture;
    spriteCard.setTexture(textureCard);
}