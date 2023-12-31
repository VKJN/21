#include "Header.h"
#include "Game.h"
#include "Config.h"

Game::Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck, int CardsInDeck
    /*sf::RenderWindow& window, sf::Event& event, sf::RectangleShape& background*/) {
    this->enemy = enemy;
    this->player = player;
    this->deck = deck;

    this->CounterPass = 0;
    this->CardsInDeck = CardsInDeck;
    this->winningNumber = 21;

    /*this->window.create(window.getSystemHandle());
    this->event = event;
    this->background = background;*/

    if (!font.loadFromFile("fonts/comicz.ttf")) {
        // error...
    }
    text.setFont(font);
}

void Game::Play(sf::RenderWindow& window, sf::RectangleShape& background) {
    //window.setMouseCursorVisible(false);
    do {
        Round(window, background);
        RoundResult(CheckWinner(), window, background);
        if (player.GetLife() > 0 && enemy.GetLife() > 0) {
            RestartRound();
        }
    } while (player.GetLife() > 0 && enemy.GetLife() > 0);
   
    if (player.GetLife() <= 0) {
        SetText("You lose in game", menuTextColor, tricknessSize, 45, 0);
        show(window, background);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    else if (enemy.GetLife() <= 0) {
        SetText("You win in game", menuTextColor, tricknessSize, 45, 0);
        show(window, background);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::Round(sf::RenderWindow& window, sf::RectangleShape& background) {
    SetText("New round", menuTextColor, tricknessSize, 45, 0);

    // ������ ����� New round � �������� 2 �������
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
            SetText("Your move", menuTextColor, tricknessSize, 45, 0);
            show(window, background);
            try {
                player.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber, window);
            }
            catch (const char* error_message) {   // ����� ������, ��� ������� + �������� 2 �������, ����� ��������
                SetText(error_message, menuTextColor, tricknessSize, 45, 0);
                show(window, background);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        else {
            SetText("Enemy move", menuTextColor, tricknessSize, 45, 0);
            show(window, background);

            enemy.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber, window);
        }

        SetText("", menuTextColor, tricknessSize, 45, 0);
        show(window, background);

    } while (CounterPass < 2);
}

void Game::show(sf::RenderWindow& window, sf::RectangleShape& background) {
    window.clear();
    window.draw(background);

    player.showCards(window);
    player.showLifes(window);

    enemy.showCards(window);
    enemy.showLifes(window);

    window.draw(text);

    SetText("? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber), sf::Color::White, 3, 30, 1);
    window.draw(text);

    SetText(std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber), sf::Color::White, 3, 30, 2);
    window.draw(text);

    SetText(std::to_string(player.GetFirstCardNumber()), sf::Color::White, 3, 30, 3);
    window.draw(text);

    window.display();
}

int Game::AfterThePlay(sf::RenderWindow& window, sf::RectangleShape& background) {
    SetText("Do you want to play again? Y/N", menuTextColor, tricknessSize, 70, 0);
    bool result = false;
    while (!result) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            result = true;

            player.SetLife(5);
            player.ChangeLifeTexture(0);

            enemy.SetLife(5);
            enemy.ChangeLifeTexture(0);

            RestartRound();
            return 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            result = true;
            return 0;
        }
        window.clear();
        window.draw(background);
        window.draw(text);
        window.display();
    }
}

int Game::CheckWinner() {
    /*
        ��������, ������� ����� ������� �������:
        1 - �����, ��� ���������
        2 - ������ ������
        3 - ������ ����������
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

void Game::RoundResult(int result, sf::RenderWindow& window, sf::RectangleShape& background) {

    std::this_thread::sleep_for(std::chrono::seconds(1));

    player.ChangeFirstCardTexture();
    enemy.ChangeFirstCardTexture();

    if (result == 1) {
        SetText("Draw", menuTextColor, tricknessSize, 45, 0);
        show(window, background);

        player.ChangeLifeTexture(1);
        enemy.ChangeLifeTexture(1);

        player.SetLife(player.GetLife() - player.GetBid());
        enemy.SetLife(enemy.GetLife() - enemy.GetBid());

        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetText("Draw", menuTextColor, tricknessSize, 45, 0);
        show(window, background);
    }

    else if (result == 2) {
        SetText("You win", menuTextColor, tricknessSize, 45, 0);
        show(window, background);

        enemy.ChangeLifeTexture(1);

        enemy.SetLife(enemy.GetLife() - enemy.GetBid());

        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetText("You win", menuTextColor, tricknessSize, 45, 0);
        show(window, background);
    }

    else {
        SetText("You lose", menuTextColor, tricknessSize, 45, 0);
        show(window, background);

        player.ChangeLifeTexture(1);

        player.SetLife(player.GetLife() - player.GetBid());

        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetText("You lose", menuTextColor, tricknessSize, 45, 0);
        show(window, background);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Game::RestartRound() {

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

void Game::SetText(std::string newText, sf::Color newColor, int thickness, int size, int trigger) {
    text = sf::Text(newText, font, size);
    text.setFillColor(newColor);
    text.setOutlineThickness(thickness);

    switch (trigger) {
    case 0:
        text.setPosition((WIDTH - text.getLocalBounds().width) / 2, (HEIGHT - text.getLocalBounds().height) / 2);
        break;
    case 1: 
        text.setPosition((WIDTH - text.getLocalBounds().width) / 1.4, (HEIGHT - text.getLocalBounds().height) / 3);
        break;
    case 2:
        text.setPosition((WIDTH - text.getLocalBounds().width) / 1.4, (HEIGHT - text.getLocalBounds().height) / 1.5);
        break;
    case 3:
        text.setPosition(WIDTH * 0.375, HEIGHT * 0.95);
        break;
    }
}