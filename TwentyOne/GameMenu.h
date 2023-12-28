#pragma once

class GameMenu {
private:
	float menuX;
	float menuY;
	int menuStep;
	int sizeFont;           
	int mainMenuSelected;

	std::string rulesPath = "Rules.txt";

	sf::Font font;

	std::vector<sf::Text> mainMenu;
	std::vector<sf::Text> textFromFile;
	int textPosX = 250, textPosY = 500;

	sf::Color menuColor;
		
	void setInitText(sf::Text& text, std::string& str, float xpos, float ypos, sf::Color color, int fontSize);

	void OpenRules(sf::RenderWindow& window, sf::RectangleShape& background, sf::Event event);
public:
	GameMenu(float menux, float menuy, int sizeFont, int step, std::vector<std::string>& name);

	void draw(sf::RenderWindow& window);
		
	void setColorTextMenu(sf::Color color);

	void AlignMenu();

	bool GamePlayMenu(sf::RenderWindow& window, sf::RectangleShape& background, sf::Text& titul, sf::Event event);
};