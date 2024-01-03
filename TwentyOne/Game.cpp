#include "Header.h"
#include "Game.h"

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

    if (!font.loadFromFile("fonts/ariali.ttf")) {
        // error...
    }
    text.setFont(font);
}

void Game::Play() {
    do {
        Round();
        RoundResult(CheckWinner());
        if (player.GetLife() > 0 || enemy.GetLife() > 0) {
            RestartRound();
        }
        show();
    } while (player.GetLife() > 0 && enemy.GetLife() > 0);
   
    if (player.GetLife() <= 0) {
        std::cout << "You lose in game";
    }
    else if (enemy.GetLife() <= 0) {
        std::cout << "You win in game";
    }
}

void Game::Round() {
    std::cout << "New round" << std::endl;
    //AddText("New round", sf::Color::White, 30, window);             // Сделать, чтобы текст был на экране только 2 секунды
    //window.draw(text);
    //window.display();
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    
    WHOMOVE = random(0, 1);
    do {
        std::cout << "Enemy card sum: " << enemy.GetCardSum() << "/" << winningNumber << "\n";
        std::cout << "Your card sum: " << player.GetCardSum() << "/" << winningNumber << "\n";
        std::cout << "CounterPass: " << CounterPass << "\n\n\n";

        show();

        if (WHOMOVE) {
            player.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber, window);
        }
        else {
            enemy.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber, window);
        }

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
        player.ChangeLifeTexture();
        enemy.ChangeLifeTexture();

        player.SetLife(player.GetLife() - player.GetBid());
        enemy.SetLife(enemy.GetLife() - enemy.GetBid());
        std::cout << "Draw" << std::endl;
    }

    else if (result == 2) {
        enemy.ChangeLifeTexture();

        enemy.SetLife(enemy.GetLife() - enemy.GetBid());
        std::cout << "You win" << std::endl;
    }

    else {
        player.ChangeLifeTexture();

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

    CardsInDeck = 11;

    AddInDeck(deck, CardsInDeck);
    for (int i = 0; i < 2; i++) {
        player.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), CardsInDeck));
        enemy.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), CardsInDeck));
    }
}

void Game::AddText(std::string newText, sf::Color newColor, int size) {
    text = sf::Text(newText, font, size);
    text.setFillColor(newColor);
    text.setPosition((window.getSize().x - text.getLocalBounds().width) / 2,
        (window.getSize().y - text.getLocalBounds().height) / 2);
}