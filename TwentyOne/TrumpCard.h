#pragma once
#include "Header.h"
/*
	 Все козыри и их кол-во в колоде: 
	 1) Карта 2-7 (по 1)
	 2) +1 и +2 (2 и 4)
	 3) Возврат, удаление, обмен (по 4)
	 4) Цель 17, 24 и 27 (по 1)
	 5) Щит (4)
	 Всего: 31

	 Значение козырей (по номерам):
	 1) Вытягивается карта 2-7 из колоды. Если такой нет, то ничего не происходит
	 2) Добавляет +1 или +2 к ставке противника
	 3) Возвращает свою последнюю карту в колоду; Удаляет последнюю карту противника, она переходит в колоду; обмен последними картами
	 4) Меняется выйгрышное число
	 5) Уменьшает твою ставку на 1
 */

class TrumpCard {
private:
	int id;
	sf::Texture textureCard;
	sf::Sprite spriteCard;
public:
	TrumpCard(int id, sf::Texture& texture_card);
	TrumpCard(const TrumpCard& copy);

	void Show(sf::RenderWindow& window);

	void setTextureCardPosition(int posX, int posY);
	void setScale(int x, int y);

	void changeTexture(sf::Texture newTexture);

	sf::FloatRect getPosition();

	int getId();

	void setTexture();
};