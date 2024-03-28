#include "Header.h"
#include "Game.h"
#include "Config.h"

Game::Game(CardDeck& deck, int CardsInDeck, sf::RenderWindow & window_, sf::RectangleShape background_)
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

    windowTrump = sf::RectangleShape(sf::Vector2f(WIDTH / 2, HEIGHT));
    windowTrump.setPosition(sf::Vector2f(WIDTH / 2, 0));
    windowTrump.setFillColor(sf::Color(0, 0, 0, 128));
}

void Game::Play() {
    do {
        // Колода козырей (она прописана тут, так как в самом начале у игроков 0 козырей и в течении все игры колода не должна обновляться)
        CardsInTrumpDeck = 31;
        AddInDeck(trumpDeck, CardsInTrumpDeck);

        // Обновление текста, отвечающего за показ сумм карт и моей закрытой карты
        yourCloseCard.setString(std::to_string(player.GetFirstCardNumber()));
        yourCardSum.setString(std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber));
        enemyCardSum.setString("? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber));

        yourBet.setString("Your bet: " + std::to_string(player.GetBet()));
        enemyBet.setString("Enemy bet: " + std::to_string(enemy.GetBet()));

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
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.scancode == sf::Keyboard::Scan::Num1) {
                visible = !visible;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            yourMove = 0;
        }

        if (visible) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                yourMove = 4;
            }
        }

        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                yourMove = 2;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                yourMove = 3;
            }
        }
    }
}

void Game::update() {
    if (WHOMOVE) {
        switch (yourMove) {
        case 0:
            window.close();
            std::exit(0);
            break;

        case 2:
            try {
                player.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber);

                int chance = random(1, 10);

                if (chance < 11 && trumpDeck.GetCardCounter() != 0) {
                    player.TakeTrump(trumpDeck.RemoveCard(random(1, trumpDeck.GetCardCounter()), CardsInTrumpDeck));
                }
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

        case 4:
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            bool result = player.handleMouseClick(mousePosition);
            if (result) {
                visible = !visible;
                CounterPass = 0; // Для того, чтобы противник смог ответить на козырь во время своего следующего хода
                try {
                    whatTrumpCard(player.getTrumpsShown(), player);
                }
                catch (const char* error_message) {
                    text.setString(error_message);
                    text.setPosition((WIDTH - text.getLocalBounds().width) / 2, (HEIGHT - text.getLocalBounds().height) / 2);

                    render(1, text);
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            }
        }
        yourMove = -1;
    }
        
    else {
        /*
        * terrible implementation, but I don’t know how to do it differently
        */
        int result;
        do {
            result = enemy.Move(deck, WHOMOVE, CounterPass, CardsInDeck, winningNumber, player);
            if (result == 1) {
                try {
                    whatTrumpCard(enemy.getTrumpsShown(), enemy);
                }
                catch (const char* error_message) {
                    std::cout << "Enemy: " << error_message << std::endl;
                }
            }

            // timely updating so that there is no sudden appearance of trumps and cards
            yourCardSum.setString(std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber));
            enemyCardSum.setString("? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber));

            yourBet.setString("Your bet: " + std::to_string(player.GetBet()));
            enemyBet.setString("Enemy bet: " + std::to_string(enemy.GetBet()));

            render(1, textReplicas[2]);
        } while (result == 1);

        if (result == 0) {
            int chance = random(1, 10);

            if (chance < 6 && trumpDeck.GetCardCounter() != 0) {
                enemy.TakeTrump(trumpDeck.RemoveCard(random(1, trumpDeck.GetCardCounter()), CardsInTrumpDeck));
            }
        }
    }

    enemyCardSum.setString("? + " + std::to_string(enemy.GetCardSum() - enemy.GetFirstCardNumber()) + " / " + std::to_string(winningNumber));
    yourCardSum.setString(std::to_string(player.GetCardSum()) + " / " + std::to_string(winningNumber));

    yourBet.setString("Your bet: " + std::to_string(player.GetBet()));
    enemyBet.setString("Enemy bet: " + std::to_string(enemy.GetBet()));
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

        window.draw(yourBet);
        window.draw(enemyBet);

        if (visible) { 
            window.draw(windowTrump); 
            player.showTrumpInventory(window);
        }

        window.display();
        break;
    }
}

void Game::whatTrumpCard(std::vector<TrumpCard>& trumps, Player& who) {
    Card lastY, lastE;
    int result;
    int trumpId = trumps.back().getId();

    switch (trumpId) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        result = deck.cardSearch(trumpId + 1);
        if (result != -1) {
            who.TakeCard(deck.RemoveCard(result + 1, CardsInDeck));
        }
        else throw "There is no card in the deck";
        break;

    case 7:
        if (who.GetBet() != 0) {
            who.SetBet(who.GetBet() - 1);
        }
        break;
    
    // Удаление карты противника
    case 8:
        if (WHOMOVE) {
            if (enemy.GetCardSum() != enemy.GetFirstCardNumber()) {
                enemy.SetCardSum(enemy.GetCardSum() - enemy.removeLastCard().GetNumber());
            }
        }

        else {
            if (player.GetCardSum() != player.GetFirstCardNumber()) {
                player.SetCardSum(player.GetCardSum() - player.removeLastCard().GetNumber());
            }
        }
        break;

    // Удаление своей карты
    case 9:
        if (who.GetCardSum() != who.GetFirstCardNumber()) {
            who.SetCardSum(who.GetCardSum() - who.removeLastCard().GetNumber());
        }
        break;

    // Обмен картами
    case 10:
        if (player.GetCardSum() != player.GetFirstCardNumber() && enemy.GetCardSum() != enemy.GetFirstCardNumber()) {
            lastY = player.removeLastCard();
            player.SetCardSum(player.GetCardSum() - lastY.GetNumber());

            lastE = enemy.removeLastCard();
            enemy.SetCardSum(enemy.GetCardSum() - lastE.GetNumber());

            player.TakeCard(lastE);
            enemy.TakeCard(lastY);
        }
        break;

    case 11:
        winningNumber = 17;
        break;

    case 12:
        winningNumber = 24;
        break;

    case 13:
        winningNumber = 27;
        break;

    case 14:
    case 15:
        WHOMOVE ? enemy.SetBet(enemy.GetBet() + (trumpId - 13)) : player.SetBet(player.GetBet() + (trumpId - 13));
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
            // Колода для козырей должна очищаться только при окончании игры, и заполняться в начале
            trumpDeck.ClearDeck(); 
            player.ClearInventory();
            enemy.ClearInventory();
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

        player.SetLife(player.GetLife() - player.GetBet());
        enemy.SetLife(enemy.GetLife() - enemy.GetBet());

        player.ChangeLifeTexture(1);
        enemy.ChangeLifeTexture(1);
        break;

    case 2:
        render(1, textReplicas[4]);

        enemy.SetLife(enemy.GetLife() - enemy.GetBet());

        enemy.ChangeLifeTexture(1);
        break;

    case 3:
        render(1, textReplicas[5]);

        player.SetLife(player.GetLife() - player.GetBet());

        player.ChangeLifeTexture(1);
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

    player.SetBet(1);
    enemy.SetBet(1);

    winningNumber = 21;

    CardsInDeck = 11;

    AddInDeck(deck, CardsInDeck);

    for (int i = 0; i < 2; i++) {
        player.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), CardsInDeck));
        enemy.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter()), CardsInDeck));
    }
}

void Game::addText() {
    for (int i = 0; i < 15; i++) {
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
            switch (i) {
            case 10:
                text.setPosition(WIDTH * 0.375, HEIGHT * 0.95);
                yourCloseCard = text;
                break;

            case 11:
                text.setPosition((WIDTH - text.getLocalBounds().width) / 6, (HEIGHT - text.getLocalBounds().height) / 1.4);
                yourCardSum = text;
                break;

            case 12:
                text.setPosition((WIDTH - text.getLocalBounds().width) / 6, (HEIGHT - text.getLocalBounds().height) / 2.6);
                enemyCardSum = text;
                break;

            case 13:
                text.setPosition(WIDTH / 6, HEIGHT / 1.5);
                yourBet = text;
                break;

            case 14:
                text.setPosition(WIDTH / 6, HEIGHT / 3);
                enemyBet = text;
                break;
            }
        }
    }
    text = textReplicas[9];
}