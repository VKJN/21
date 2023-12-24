#pragma once

class GameMenu {
private:
	float menuX;
	float menuY;
	int menuStep;
	int sizeFont;           
	int mainMenuSelected;

	sf::Font font;
	std::vector<sf::Text> mainMenu;
		
	void setInitText(sf::Text& text, std::string& str, float xpos, float ypos); 
public:

	GameMenu(float menux, float menuy, int sizeFont, int step, std::string name[]);

	void draw(sf::RenderWindow& window);

	void AlignMenu();
};