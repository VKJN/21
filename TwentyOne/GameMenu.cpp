#include "Header.h"
#include "Config.h"
#include "GameMenu.h"

void GameMenu::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		if (event.type == sf::Event::Closed) {
			std::exit(0);
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			std::exit(0);
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			handleMouseClick(mousePosition);
		}

		else if (rulesOpened && event.type == sf::Event::KeyPressed) {
			rulesOpened = false; // Óñòàíîâêà ôëàãà â false ïðè íàæàòèè êíîïêè â ïðàâèëàõ
			textFromFile.clear(); // Î÷èñòêà âåêòîðà, ÷òîáû ïðè ïîâòîðíîì îòêðûòèè ôàéëà íå áûëî ïðîøëîãî òåêñòà
			textPosY = 500; // ×òîáû òåêñò íå óåçæàë âíèç

			updateMenuText();
		}
	}
}

void GameMenu::update() {
	// Ïðîâåðêà, åñëè êîîðäèíàòû ìûøè ïîïàäàþò ïî êíîïêå, îíà ìåíÿåò öâåò
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	for (int i = 0; i < mainMenu.size(); i++) {
		if (mainMenu[i].getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
			mainMenu[i].setFillColor(menuColor);
		}
		else {
			mainMenu[i].setFillColor(sf::Color::White);
		}
	}

	if (rulesOpened) {
		mainMenu.clear();
	}
}

void GameMenu::render() {
	if (rulesOpened) {
		window.clear();
		window.draw(background);

		for (auto i : textFromFile) {
			window.draw(i);
		}

		window.display();
	}

	else {
		window.clear();
		window.draw(background);
		window.draw(titul);

		for (auto i : mainMenu) {
			window.draw(i);
		}

		window.display();
	}
}

void GameMenu::initText(sf::Text& text, float posX, float posY, std::string& str, int sizeFont, sf::Color color) {	
	text.setCharacterSize(sizeFont);
	text.setPosition(posX, posY);
	text.setString(str);
	text.setFillColor(color);
	text.setOutlineThickness(tricknessSize);
	text.setFont(menuFont);
}

void GameMenu::setColorTextMenu(sf::Color color) {
	menuColor = color;
	for (auto i : mainMenu) {
		i.setFillColor(menuTextColor);
	}
}

// Ìåòîä, äëÿ óñòàíîâêè òåêñòà ïîñåðåäèíå ýêðàíà
void GameMenu::AlignMenu() {
	float nullx = 0;

	for (int i = 0; i < mainMenu.size(); i++) {
		nullx = mainMenu[i].getLocalBounds().width / 2;
		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}

// Ìåòîä, äëÿ îáíîâëåíèÿ êíîïîê ìåíþ. Âûçûâàåòñÿ â êîíñòðóêòîðå è ïîñëå ïðàâèë, òàê êàê âî âðåìÿ ïîêàçà ïðàâèë, âåêòîð ïóñòîé
void GameMenu::updateMenuText() {
	mainMenu.resize(nameMenu.size());

	for (int i = 0, posY = menuY; i < mainMenu.size(); i++, posY += menuStep) {  // posY - äëÿ ðàññòîÿíèÿ ìåæäó òåêñòîì
		initText(mainMenu[i], menuX, posY, nameMenu[i], sizeFont, menuColor);
	}

	setColorTextMenu(menuTextColor);
	AlignMenu();
}

void GameMenu::handleMouseClick(const sf::Vector2i& mousePosition) {
	for (int i = 0; i < mainMenu.size(); i++) {
		if (mainMenu[i].getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
			switch (i) {
			case 0:
				resultMenu = true;
				break;
			case 1:
				OpenRules();
				break;
			case 2:
				std::exit(0);
				window.close();
				break;
			}
		}
	}
}

void GameMenu::OpenRules() {
	std::ifstream rulesFile(rulesPath);
	std::string lineText;
	sf::Text text;

	if (rulesFile.is_open()) {
		while (std::getline(rulesFile, lineText)) {
			initText(text, textPosX, textPosY, lineText, 40, sf::Color::White);
			textFromFile.push_back(text);
			textPosY += 40;
		}
	}
	rulesFile.close();

	rulesOpened = true;
}

GameMenu::GameMenu(std::vector<std::string>& nameMenu)
	: window(sf::VideoMode::getDesktopMode(), "Twenty One", sf::Style::Fullscreen),
	/*window(sf::VideoMode(1800, 1000), "Twenty One"),*/
	background(sf::Vector2f(WIDTH, HEIGHT)), menuX(WIDTH * 0.49), menuY(HEIGHT * 0.37), menuStep(175), sizeFont(65)
{
	this->nameMenu = nameMenu;
	backgroundTexture.loadFromFile("./image/background.jpg");
	background.setTexture(&backgroundTexture);

	menuFont.loadFromFile("./fonts/comici.ttf");

	titul.setFont(menuFont);
	std::string titulText = "Twenty One";
	initText(titul, WIDTH * 0.31, 50, titulText, 125, menuTextColor);

	updateMenuText();
}

void GameMenu::GamePlayMenu() {
	while (!resultMenu && window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

sf::RenderWindow& GameMenu::getWindow() {
	return window;
}

sf::RectangleShape GameMenu::getBackground() {
	return background;
}
