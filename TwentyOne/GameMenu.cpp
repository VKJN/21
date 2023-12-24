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
	float nullx = 0;   // Переменная для того, чтобы правильно выставить на экране текст (посередине)

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

	int ypos = menuY; // Переменная для расстояния между текстом 
	int j = 0;

	for (auto i : mainMenu) {
		setInitText(i, name[j++], menuX, ypos);
		ypos += menuStep; 
	}

	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(choseTextColor);
}

void GameMenu::MoveUp() {
	mainMenuSelected--;

	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
		mainMenu[mainMenuSelected + 1].setFillColor(menuTextColor);
	}
	else {
		mainMenu[0].setFillColor(menuTextColor);
		mainMenuSelected = mainMenu.size() - 1;
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
	}
}

void GameMenu::MoveDown() {
	mainMenuSelected++;

	if (mainMenuSelected < mainMenu.size()) {
		mainMenu[mainMenuSelected - 1].setFillColor(menuTextColor);
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
	}
	else {
		mainMenu[mainMenu.size() - 1].setFillColor(menuTextColor);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(choseTextColor);
	}

}

void GameMenu::draw(sf::RenderWindow& window) {
	for (auto i : mainMenu) {
		window.draw(i);
	}
}

void GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor) {
	menuTextColor = menColor;
	choseTextColor = ChoColor;

	for (auto i : mainMenu) {
		i.setFillColor(menuTextColor);
		i.setOutlineColor(borderColor);
	}
	mainMenu[mainMenuSelected].setFillColor(choseTextColor);
}