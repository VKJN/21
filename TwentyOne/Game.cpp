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

    // Заполнение вектора текстов
    /*for (int i = 0; i < 9; i++) {
        text.setString(replicas[i]);
        text.setCharacterSize(i != 8 ? 45 : 70);
        text.setFillColor(menuTextColor);
        text.setOutlineThickness(thicknessSize);
        text.setPosition((WIDTH - text.getLocalBounds().width) / 2, (HEIGHT - text.getLocalBounds().height) / 2);

        textReplicas.push_back(text);
    }*/
}

void Game::Play() {
    do {
        // Обновление текста, отвечающего за показ сумм карт и моей закрытой карты
        SetText(yourCloseCard, std::to_string(player.GetFirstCardNumber()), sf::Color::White, 3, 30, 3);
        SetText(yourCardSum, std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber), sf::Color::White, 3, 30, 2);
        SetText(enemyCardSum, "? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber), sf::Color::White, 3, 30, 1);

        // Вывод на экран текста New round + ожидание 2 секунды
        SetText(text, replicas[0], menuTextColor, thicknessSize, 45, 0);
        render(0);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        Round();
        RoundResult(CheckWinner());
        if (player.GetLife() > 0 && enemy.GetLife() > 0) {
            RestartRound();
        }
    } while (player.GetLife() > 0 && enemy.GetLife() > 0);
   // Почему-то при окончании игры, условие в while продолжает выполняться

    /*if (player.GetLife() <= 0 && enemy.GetLife() > 0) {
        SetText(text, replicas[6], menuTextColor, thicknessSize, 45, 0);
        render(1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    else if (enemy.GetLife() <= 0 && player.GetLife() > 0) {
        SetText(text, replicas[7], menuTextColor, thicknessSize, 45, 0);
        render(1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    else {
        SetText(text, replicas[3], menuTextColor, thicknessSize, 45, 0);
        render(1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }*/
}

void Game::Round() {
    WHOMOVE = random(0, 1);

    while (CounterPass < 2) {
        WHOMOVE ? SetText(text, replicas[1], menuTextColor, thicknessSize, 45, 0) : SetText(text, replicas[2], menuTextColor, thicknessSize, 45, 0);
        render(1);
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
                SetText(text, error_message, menuTextColor, thicknessSize, 45, 0);
                render(1);
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

    SetText(enemyCardSum, "? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber), sf::Color::White, 3, 30, 1);
    SetText(yourCardSum, std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber), sf::Color::White, 3, 30, 2);
}

void Game::render(int trigger) {
    switch (trigger) {
    case 0:
        window.clear();
        window.draw(background);
        window.draw(text);
        window.display();
        break;
    case 1:
        window.clear();
        window.draw(background);

        player.showCards(window);
        player.showLifes(window);

        enemy.showCards(window);
        enemy.showLifes(window);

        window.draw(text);

        window.draw(yourCardSum);
        window.draw(yourCloseCard);
        window.draw(enemyCardSum);

        window.display();
        break;
    }
}

int Game::AfterThePlay() {
    SetText(text, replicas[8], menuTextColor, thicknessSize, 70, 0);
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
        render(0);
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
    SetText(text, "", menuTextColor, thicknessSize, 45, 0);
    render(1);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    player.ChangeFirstCardTexture();
    enemy.ChangeFirstCardTexture();

    if (result == 1) {
        SetText(text, replicas[3], menuTextColor, thicknessSize, 45, 0);
        render(1);

        player.ChangeLifeTexture(1);
        enemy.ChangeLifeTexture(1);

        player.SetLife(player.GetLife() - player.GetBid());
        enemy.SetLife(enemy.GetLife() - enemy.GetBid());

        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetText(text, replicas[3], menuTextColor, thicknessSize, 45, 0);
        render(1);
    }

    else if (result == 2) {
        SetText(text, replicas[4], menuTextColor, thicknessSize, 45, 0);
        render(1);

        enemy.ChangeLifeTexture(1);

        enemy.SetLife(enemy.GetLife() - enemy.GetBid());

        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetText(text, replicas[4], menuTextColor, thicknessSize, 45, 0);
        render(1);
    }

    else {
        SetText(text, replicas[5], menuTextColor, thicknessSize, 45, 0);
        render(1);

        player.ChangeLifeTexture(1);

        player.SetLife(player.GetLife() - player.GetBid());

        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetText(text, replicas[5], menuTextColor, thicknessSize, 45, 0);
        render(1);
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

void Game::SetText(sf::Text& text, std::string newText, sf::Color newColor, int thickness, int size, int trigger) {
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