#include "Header.h"
#include "Game.h"
#include "Config.h"

Game::Game(CardDeck& deck, int CardsInDeck, sf::RenderWindow& window_, sf::RectangleShape background_)
    : window(window_),
    background(background_),
    deck(deck),
    CardsInDeck(CardsInDeck),
    player(deck.RemoveCard(random(1, CardsInDeck), CardsInDeck), deck.RemoveCard(random(1, CardsInDeck), CardsInDeck)),
    enemy(deck.RemoveCard(random(1, CardsInDeck), CardsInDeck), deck.RemoveCard(random(1, CardsInDeck), CardsInDeck))
{
    this->CounterPass = 0;
    this->winningNumber = 21;

    if (!font.loadFromFile("fonts/comicz.ttf")) {
        // error...
    }

    text.setFont(font);

    // Заполнение вектора текстов и остального текста
    addText();
}

void Game::Play() {
    do {
        // Обновление текста, отвечающего за показ сумм карт и моей закрытой карты
        yourCloseCard.setString(std::to_string(player.GetFirstCardNumber()));
        yourCardSum.setString(std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber));
        enemyCardSum.setString("? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber));

        // Вывод на экран текста New round + ожидание 2 секунды
        render(0, textReplicas[0]);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Сама игра
        Round();
        RoundResult(CheckWinner());
        if (player.GetLife() > 0 && enemy.GetLife() > 0) {
            RestartRound();
        }
    } while (player.GetLife() > 0 && enemy.GetLife() > 0);

    if (player.GetLife() <= 0 && enemy.GetLife() > 0) {
        render(1, textReplicas[6]);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    else if (enemy.GetLife() <= 0 && player.GetLife() > 0) {
        render(1, textReplicas[7]);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    else {
        render(1, textReplicas[3]);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::Round() {
    WHOMOVE = random(0, 1);

    while (CounterPass < 2) {
        WHOMOVE ? render(1, textReplicas[1]) : render(1, textReplicas[2]);
        processEvents();
        update();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            yourMove = 2;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            yourMove = 3;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            yourMove = 0;
        }
    }
}

void Game::update() {
    if (WHOMOVE) {
        switch (yourMove) {
        case 2:
            try {
                player.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber);
            }
            // Вывод ошибки, что перебор + ожидание 2 секунды, чтобы прочесть
            catch (const char* error_message) {
                text.setString(error_message);
                text.setPosition((WIDTH - text.getLocalBounds().width) / 2, (HEIGHT - text.getLocalBounds().height) / 2);
                
                render(1, text);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            break;
        case 3:
            player.Pass(WHOMOVE, CounterPass);
            break;
        case 0:
            window.close();
            std::exit(0);
            break;
        }
        yourMove = -1;
    }

    else {
        enemy.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber);
    }

    enemyCardSum.setString("? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber));
    yourCardSum.setString(std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber));
}

void Game::render(int trigger, sf::Text textToRender) {
    switch (trigger) {
    case 0:
        window.clear();
        window.draw(background);
        window.draw(textToRender);
        window.display();
        break;
    case 1:
        window.clear();
        window.draw(background);

        player.showCards(window);
        player.showLifes(window);

        enemy.showCards(window);
        enemy.showLifes(window);

        window.draw(textToRender);

        window.draw(yourCardSum);
        window.draw(yourCloseCard);
        window.draw(enemyCardSum);

        window.display();
        break;
    }
}

int Game::AfterThePlay() {
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
        render(0, textReplicas[8]);
    }
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
    render(1, textReplicas[9]);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    player.ChangeFirstCardTexture();
    enemy.ChangeFirstCardTexture();

    switch (result) 
    {
    case 1:
        render(1, textReplicas[3]);

        player.ChangeLifeTexture(1);
        enemy.ChangeLifeTexture(1);

        player.SetLife(player.GetLife() - player.GetBid());
        enemy.SetLife(enemy.GetLife() - enemy.GetBid());
        break;

    case 2:
        render(1, textReplicas[4]);

        enemy.ChangeLifeTexture(1);

        enemy.SetLife(enemy.GetLife() - enemy.GetBid());
        break;

    case 3:
        render(1, textReplicas[5]);

        player.ChangeLifeTexture(1);

        player.SetLife(player.GetLife() - player.GetBid());
        break;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    render(1, ((result == 1) ? textReplicas[3] : (result == 2) ? textReplicas[4] : textReplicas[5]));
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

void Game::addText() {
    for (int i = 0; i < 13; i++) {
        if (i < 10) {
            text.setString(replicas[i]);
            text.setCharacterSize(i != 8 ? 45 : 70);
            text.setFillColor(menuTextColor);
            text.setOutlineThickness(thicknessSize);
            text.setPosition((WIDTH - text.getLocalBounds().width) / 2, (HEIGHT - text.getLocalBounds().height) / 2);

            textReplicas.push_back(text);
        }
        else {
            text.setCharacterSize(30);
            text.setFillColor(sf::Color::White);
            text.setOutlineThickness(thicknessSize);
            switch (i)
            {
            case 10:
                text.setPosition(WIDTH * 0.375, HEIGHT * 0.95);
                yourCloseCard = text;
                break;

            case 11:
                text.setPosition((WIDTH - text.getLocalBounds().width) / 1.4, (HEIGHT - text.getLocalBounds().height) / 1.5);
                yourCardSum = text;
                break;

            case 12:
                text.setPosition((WIDTH - text.getLocalBounds().width) / 1.4, (HEIGHT - text.getLocalBounds().height) / 3);
                enemyCardSum = text;
                break;
            }
        }
    }
    text = textReplicas[9];
}