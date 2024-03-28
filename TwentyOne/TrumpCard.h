#pragma once
#include "Header.h"
/*
	 ��� ������ � �� ���-�� � ������: 
	 1) ����� 2-7 (�� 1)
	 2) +1 � +2 (2 � 4)
	 3) �������, ��������, ����� (�� 4)
	 4) ���� 17, 24 � 27 (�� 1)
	 5) ��� (4)
	 �����: 31

	 �������� ������� (�� �������):
	 1) ������������ ����� 2-7 �� ������. ���� ����� ���, �� ������ �� ����������
	 2) ��������� +1 ��� +2 � ������ ����������
	 3) ���������� ���� ��������� ����� � ������; ������� ��������� ����� ����������, ��� ��������� � ������; ����� ���������� �������
	 4) �������� ���������� �����
	 5) ��������� ���� ������ �� 1
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