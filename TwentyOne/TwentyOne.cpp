#include "Header.h"
#include "Config.h"
#include "GameMenu.h"
#include "Game.h"

int main()
{
    srand(time(NULL));

    std::vector<std::string> nameMenu{ "Play", "Rules", "About trump cards", "Exit"};
    GameMenu gameMenu(nameMenu);

    int CardsInDeck = 11;
    CardDeck deck;
    Game* game21;
    while (true) {
        gameMenu.GamePlayMenu();

        // Колода обычных карт
        AddInDeck(deck, CardsInDeck);

        game21 = new Game(deck, CardsInDeck, gameMenu.getWindow(), gameMenu.getBackground());

        int result = 0;

        do {
            game21->Play();
            result = game21->AfterThePlay();
        } while (result == 1);

        deck.ClearDeck();
    }
}