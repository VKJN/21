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

	sf::Color menuTextColor = sf::Color::White;
	sf::Color choseTextColor = sf::Color::Yellow;
	sf::Color borderColor = sf::Color::Black;
		
	void setInitText(sf::Text& text, std::string& str, float xpos, float ypos); 
public:

	GameMenu(float menux, float menuy, int sizeFont, int step, std::string name[]);

	void draw(sf::RenderWindow& window);

	void MoveUp();               

	void MoveDown();   
		
	void setColorTextMenu(sf::Color menColor, sf::Color ChoColor);

	void AlignMenu();
};