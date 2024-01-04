#include "Header.h"
#include "Game.h"
#include "Config.h"

Game::Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck, int CardsInDeck,
    sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& background) {
    this->enemy = enemy;
    this->player = player;
    this->deck = deck;

    this->CounterPass = 0;
    this->CardsInDeck = CardsInDeck;
    this->winningNumber = 21;

    this->window.create(window.getSystemHandle());
    this->event = event;
    this->background = background;

    if (!font.loadFromFile("fonts/comicz.ttf")) {
        // error...
    }
    text.setFont(font);
}

void Game::Play() {
    do {
        Round();
        RoundResult(CheckWinner());
        if (player.GetLife() > 0 && enemy.GetLife() > 0) {
            RestartRound();
        }
    } while (player.GetLife() > 0 && enemy.GetLife() > 0);
   
    if (player.GetLife() <= 0) {
        AddText("You lose in game", menuTextColor, tricknessSize, 45);
        show();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    else if (enemy.GetLife() <= 0) {
        AddText("You win in game", menuTextColor, tricknessSize, 45); 
        show();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::Round() {
    AddText("New round", menuTextColor, tricknessSize, 45);

    // Просто вызов New round и ожидание 2 секунды
    window.clear();
    window.draw(background);
    window.draw(text);
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    WHOMOVE = random(0, 1);
    do {
        std::cout << "Enemy card sum: " << enemy.GetCardSum() << "/" << winningNumber << "\n";
        std::cout << "Your card sum: " << player.GetCardSum() << "/" << winningNumber << "\n";
        std::cout << "CounterPass: " << CounterPass << "\n\n\n";

        if (WHOMOVE) {
            AddText("Your move", menuTextColor, tricknessSize, 45);
            show();
            try {
                player.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber, window);
            }
            catch (const char* error_message) {   // Вывод ошибки, что у вас перебор + ожидание 2 секунды, чтобы успели прочесть
                AddText(error_message, menuTextColor, tricknessSize, 45);
                show();
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        else {
            AddText("Enemy move", menuTextColor, tricknessSize, 45);
            show();

            enemy.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber, window);
        }

        AddText("", menuTextColor, tricknessSize, 45);
        show();

    } while (CounterPass < 2);
}

void Game::show() {
    window.clear();
    window.draw(background);

    player.showCards(window);
    player.showLifes(window);

    enemy.showCards(window);
    enemy.showLifes(window);

    window.draw(text);

    window.display();
}

int Game::CheckWinner() {
    /*
        Значения, которые может вернуть функция:
        1 - ничья, оба проиграли
        2 - победа игрока
        3 - победа противника
    */
    int playerSum = player.GetCardSum();
    int enemySum = enemy.GetCardSum();

    if (playerSum == enemySum) {
        return 1;
    }
    else if ((playerSum > winningNumber) && (enemySum > winningNumber)) {
        return (playerSum < enemySum) ? 2 : 3;
    }
    else if ((playerSum < winningNumber) && (enemySum < winningNumber)) {
        return (playerSum > enemySum) ? 2 : 3;
    }
    else if ((playerSum < winningNumber) && (enemySum > winningNumber)) {
        return 2;
    }
    else if ((playerSum > winningNumber) && (enemySum < winningNumber)) {
        return 3;
    }
    else if (playerSum == winningNumber && enemySum != winningNumber) {
        return 2;
    }
    else {
        return 3;
    }
}

void Game::RoundResult(int result) {

    std::this_thread::sleep_for(std::chrono::seconds(2));

    if (result == 1) {
        enemy.ChangeFirstCardTexture();

        AddText("Draw", menuTextColor, tricknessSize, 45);
        show();

        player.ChangeLifeTexture();
        enemy.ChangeLifeTexture();

        player.SetLife(player.GetLife() - player.GetBid());
        enemy.SetLife(enemy.GetLife() - enemy.GetBid());

        show();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    else if (result == 2) {
        enemy.ChangeFirstCardTexture();

        AddText("You win", menuTextColor, tricknessSize, 45);
        show();

        enemy.ChangeLifeTexture();

        enemy.SetLife(enemy.GetLife() - enemy.GetBid());

        show();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    else {
        enemy.ChangeFirstCardTexture();

        AddText("You lose", menuTextColor, tricknessSize, 45);
        show();

        player.ChangeLifeTexture();

        player.SetLife(player.GetLife() - player.GetBid());

        show();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void Game::RestartRound() {
    //player.SetBid(1);
    //enemy.SetBid(1);

    CounterPass = 0;

    deck.ClearDeck();
    player.ClearArray();
    enemy.ClearArray();

    player.SetCardSum(0);
    enemy.SetCardSum(0);

    CardsInDeck = 11;

    AddInDeck(deck, CardsInDeck);
    for (int i = 0; i < 2; i++) {
        player.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), CardsInDeck));
        enemy.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), CardsInDeck));
    }
}

void Game::AddText(std::string newText, sf::Color newColor, int thickness, int size) {
    text = sf::Text(newText, font, size);
    text.setFillColor(newColor);
    text.setOutlineThickness(thickness);
    text.setPosition((WIDTH - text.getLocalBounds().width) / 2,
        (HEIGHT - text.getLocalBounds().height) / 2);
}