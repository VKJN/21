#include "Header.h"
#include "Config.h"
#include "GameMenu.h"
#include "Game.h"

int main()
{
    srand(time(NULL));

    std::vector<std::string> nameMenu{ "Play", "Rules", "Exit" };
    GameMenu gameMenu(nameMenu);
    
    gameMenu.GamePlayMenu();

    // Колода обычных карт
    int CardsInDeck = 11;
    CardDeck deck;
    AddInDeck(deck, CardsInDeck);

    Game game21(deck, CardsInDeck, gameMenu.getWindow(), gameMenu.getBackground());
    game21.Play();

    int result = 0;

    do {
        game21.Play();
        result = game21.AfterThePlay();
    } while (result == 1);

}