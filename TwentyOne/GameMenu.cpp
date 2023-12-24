#include "Header.h"
#include "GameMenu.h"

void GameMenu::setInitText(sf::Text& text, std::string& str, float xpos, float ypos) {
	text.setFont(font);
	text.setFillColor(menuTextColor);
	text.setString(str);
	text.setCharacterSize(sizeFont);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3); //const int tricknessSize = 3
}

void GameMenu::AlignMenu() {
	float nullx = 0;   // ���������� ��� ����, ����� ��������� ��������� �� ������ ����� (����������)

	for (int i = 0; i < mainMenu.size(); i++) {
		nullx = mainMenu[i].getLocalBounds().width / 2;
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}

GameMenu::GameMenu(float menux, float menuy, int sizeFont, int step, std::string name[])
	:menuX(menux), menuY(menuy), menuStep(step), sizeFont(sizeFont), mainMenu(name->size())
{
	if (!font.loadFromFile("fonts/ariali.ttf")) {
		// error...
	}

	for (int i = 0, posY = menuY; i < mainMenu.size(); i++, posY += menuStep) {  // posY - ��� ���������� ����� �������
		setInitText(mainMenu[i], name[i], menuX, posY);
	}
}

void GameMenu::draw(sf::RenderWindow& window) {
	for (auto i : mainMenu) {
		window.draw(i);
	}
}
