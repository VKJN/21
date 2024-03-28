#pragma once

class GameMenu {
private:
	sf::RenderWindow window;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Font menuFont;
	sf::Text titul;

	std::vector<sf::Text> mainMenu;
	int textPosX = 150, textPosY = 300;
	std::vector<std::string> nameMenu;

	std::vector<sf::Text> textFromFile;

	std::vector<sf::Sprite> CardsForDescription;
	std::vector<sf::Texture*> texturesForCards;
	std::vector<sf::Text> textForCards;
	bool description = false;
	std::string descriptionPath = "Description of trump cards.txt";

	sf::Color menuColor;

	float menuX;
	float menuY;
	int menuStep;
	int sizeFont;
	int mainMenuSelected;
	bool resultMenu;

	bool rulesOpened = false;
	std::string rulesPath = "Rules.txt";

	void processEvents();
	void update();
	void render();

	void initText(sf::Text& text, float posX, float posY, std::string& str, int sizeFont, sf::Color color);
	void updateMenuText();
	void setColorTextMenu(sf::Color color);
	void AlignMenu();

	void handleMouseClick(const sf::Vector2i& mousePosition);

	void OpenRules();

	void addCardsForDescription();
	void OpenDescription();
public:
	GameMenu(std::vector<std::string>& nameMenu);
	void GamePlayMenu();
	sf::RenderWindow& getWindow();
	sf::RectangleShape getBackground();
};