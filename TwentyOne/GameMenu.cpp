#include "Header.h"
#include "Config.h"
#include "GameMenu.h"

void GameMenu::setInitText(sf::Text& text, std::string& str, float xpos, float ypos, sf::Color color, int fontSize) {
	text.setFont(font);
	text.setFillColor(color);
	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(tricknessSize);
}

void GameMenu::AlignMenu() {
	float nullx = 0;   // ���������� ��� ����, ����� ��������� ��������� �� ������ ����� (����������)

	for (int i = 0; i < mainMenu.size(); i++) {
		nullx = mainMenu[i].getLocalBounds().width / 2;
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}

GameMenu::GameMenu(float menux, float menuy, int sizeFont, int step, std::vector<std::string>& name)
	:menuX(menux), menuY(menuy), menuStep(step), sizeFont(sizeFont), mainMenu(name.size())
{
	if (!font.loadFromFile("fonts/ariali.ttf")) {
		// error...
	}

	for (int i = 0, posY = menuY; i < mainMenu.size(); i++, posY += menuStep) {  // posY - ��� ���������� ����� �������
		setInitText(mainMenu[i], name[i], menuX, posY, menuColor, sizeFont);
	}
}

void GameMenu::draw(sf::RenderWindow& window) {
	for (auto i : mainMenu) {
		window.draw(i);
	}
}

void GameMenu::setColorTextMenu(sf::Color color) {
	menuColor = color;
	for (auto i : mainMenu) {
		i.setFillColor(menuColor);
	}
}

bool GameMenu::GamePlayMenu(sf::RenderWindow& window, sf::RectangleShape& background, sf::Text& titul, sf::Event event) {
	bool resultMenu = false;
	while (resultMenu == 0) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			
			// ��������, ���� ���������� ���� �������� �� ������, ��� ������ ����
			for (int i = 0; i < mainMenu.size(); i++) {
				if (mainMenu[i].getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
					mainMenu[i].setFillColor(menuColor);
				}
				else {
					mainMenu[i].setFillColor(sf::Color::White);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

					// ��������, �� ����� ������ � ���� ������
					for (int i = 0; i < mainMenu.size(); i++) {
						if (mainMenu[i].getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
							switch (i) {
							case 0:
								resultMenu = true;
								break;
							case 1:
								OpenRules(window, background, event);
								break;
							case 2:
								window.close();
								std::exit(0);
								break;
							}
						}
					}
				}
			}
		}
		window.clear();
		window.draw(background);
		window.draw(titul);
		draw(window); 
		window.display();
	}
	return resultMenu;
}

// ������� ��� ������ ������ �� �����
void GameMenu::OpenRules(sf::RenderWindow& window, sf::RectangleShape& background, sf::Event event) { 
	std::ifstream rulesFile(rulesPath);
	std::string lineText;
	sf::Text text;

	bool returnMenu = false;
	while (!returnMenu) {
		if (rulesFile.is_open()) {
			while (std::getline(rulesFile, lineText)) {
				setInitText(text, lineText, textPosX, textPosY, sf::Color::White, 40);
				textFromFile.push_back(text);
				textPosY += 40;
			}
		}
		rulesFile.close();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				returnMenu = true;
			}
		}
		window.clear();
		window.draw(background);
		for (auto i : textFromFile) {
			window.draw(i);
		}
		window.display();
	}
	textFromFile.clear(); // ������� �������, ����� ��� ��������� �������� ����� �� ���� �������� ������
	textPosY = 500; // ����� ����� �� ������ ����
}