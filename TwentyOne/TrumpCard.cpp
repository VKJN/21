#include "TrumpCard.h"

TrumpCard::TrumpCard(int id, sf::Texture& texture_card) {
    this->id = id;
    this->textureCard = texture_card;
    spriteCard.setTexture(textureCard);
}

TrumpCard::TrumpCard(const TrumpCard& copy) {
    this->id = copy.id;
    this->textureCard = copy.textureCard;
    spriteCard.setTexture(textureCard);
}

void TrumpCard::Show(sf::RenderWindow& window) {
    window.draw(spriteCard);
}

void TrumpCard::setTextureCardPosition(int posX, int posY) {
    spriteCard.setPosition(posX, posY);
}

// Метод, используемый enemy, чтобы его карты были перевернуты
void TrumpCard::setScale(int x, int y) {
    spriteCard.setScale(x, y);
}

void TrumpCard::changeTexture(sf::Texture newTexture) {
    this->textureCard = newTexture;
    spriteCard.setTexture(textureCard);
}

sf::FloatRect TrumpCard::getPosition() {
    return spriteCard.getGlobalBounds();
}

int TrumpCard::getId() {
    return id;
}

void TrumpCard::setTexture() {
    std::string path = "";
    switch (id) {
    case 1:
        path = "image/Textures for trump cards/take2.jpg";
        break;
    case 2:
        path = "image/Textures for trump cards/take3.jpg";
        break;
    case 3:
        path = "image/Textures for trump cards/take4.jpg";
        break;
    case 4:
        path = "image/Textures for trump cards/take5.jpg";
        break;
    case 5:
        path = "image/Textures for trump cards/take6.jpg";
        break;
    case 6:
        path = "image/Textures for trump cards/take7.jpg";
        break;
    case 7:
        path = "image/Textures for trump cards/shield.jpg";
        break;
    case 8:
        path = "image/Textures for trump cards/remove.jpg";
        break;
    case 9:
        path = "image/Textures for trump cards/return.jpg";
        break;
    case 10:
        path = "image/Textures for trump cards/exchange.jpg";
        break;
    case 11:
        path = "image/Textures for trump cards/go for 17.jpg";
        break;
    case 12:
        path = "image/Textures for trump cards/go for 24.jpg";
        break;
    case 13:
        path = "image/Textures for trump cards/go for 27.jpg";
        break;
    case 14:
        path = "image/Textures for trump cards/+1.jpg";
        break;
    case 15:
        path = "image/Textures for trump cards/+2.jpg";
        break;
    }
    textureCard.loadFromFile(path);
    spriteCard.setTexture(textureCard);
}