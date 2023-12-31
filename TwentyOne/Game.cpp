#include "Header.h"
#include "Game.h"

Game::Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck, int MaxCards) {
    this->enemy = enemy;
    this->player = player;
    this->deck = deck;

    this->CounterPass = 0;
    this->MaxCards = MaxCards;
    this->winningNumber = 21;

    if (!font.loadFromFile("fonts/ariali.ttf")) {
        // error...
    }
    text.setFont(font);
}

void Game::Play(sf::RenderWindow& window) {
    do {
        Round(window);
        RoundResult(CheckWinner());
        RestartRound();
    } while (player.GetLife() > 0 || enemy.GetLife() > 0);

    if (player.GetLife() <= 0) {
        std::cout << "You lose in game";
    }
    else if (enemy.GetLife() <= 0) {
        std::cout << "You win in game";
    }
}

void Game::Round(sf::RenderWindow& window) {
    std::cout << "New round" << std::endl;
    //AddText("New round", sf::Color::White, 30, window);             // Сделать, чтобы текст был на экране только 2 секунды
    //window.draw(text);
    //window.display();

    //std::this_thread::sleep_for(std::chrono::seconds(2));
    
    WHOMOVE = random(0, 1);
    do {
        enemy.showCards(window);
        std::cout << "Enemy card sum: " << enemy.GetCardSum() << "/" << winningNumber << "\n\n";

        player.showCards(window);
        std::cout << "Your card sum: " << player.GetCardSum() << "/" << winningNumber << "\n\n";

        std::cout << "CounterPass: " << CounterPass << "\n\n\n";

        if (WHOMOVE) {
            player.Move(deck, WHOMOVE, CounterPass, MaxCards, winningNumber);
        }
        else {
            enemy.Move(deck, WHOMOVE, CounterPass, MaxCards, winningNumber);
        }
    } while (CounterPass < 2);
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
    else if ((playerSum <= winningNumber) && (enemySum > winningNumber)) {
        return 2;
    }
    else {
        return 3;
    }
}

void Game::RoundResult(int result) {
    if (result == 1) {
        player.SetLife(player.GetLife() - player.GetBid());
        enemy.SetLife(enemy.GetLife() - enemy.GetBid());
        std::cout << "Draw" << std::endl;
    }

    else if (result == 2) {
        enemy.SetLife(enemy.GetLife() - enemy.GetBid());
        std::cout << "You win" << std::endl;
    }

    else {
        player.SetLife(player.GetLife() - player.GetBid());
        std::cout << "You lose" << std::endl;
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
    deck.SetCardCounter(0);

    MaxCards = 11;

    AddInDeck(deck, MaxCards);
    for (int i = 0; i < 2; i++) {
        player.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), MaxCards), winningNumber);
        enemy.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), MaxCards), winningNumber);
    }
}

void Game::AddText(std::string newText, sf::Color newColor, int size, sf::RenderWindow& window) {
    text = sf::Text(newText, font, size);
    text.setFillColor(newColor);
    text.setPosition((window.getSize().x - text.getLocalBounds().width) / 2,
        (window.getSize().y - text.getLocalBounds().height) / 2);
}