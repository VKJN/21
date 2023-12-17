#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h> 
#include <chrono>
#include <SFML/Graphics.hpp>
using namespace std;
#define random(a,b) (a+rand()%(b+1-a))

enum Napravlenie { // Keyboard
    W = 119,
    A = 97,
    S = 115,
    D = 100,
    Two = 50,
    Three = 51,
    Four = 52,
    F = 102,
    V = 118
};

bool MOVE; // true - your move, false - enemy move
int CounterPass = 0; // if 2 - opening of closed cards
int MAX_CARDS = 11;
int winningNumber = 21;

class Card {
private:
    int number;
public:
    Card(int value) {
        this->number = value;
    }
    Card(const Card& copy) {
        this->number = copy.number;
    }
    int GetNumber() const {
        return number;
    }
    void Show() {
        cout << number << " ";
    }
};

class CardDeck {
private:
    vector<Card> deck;
    int CardCounter = 0;
public:
    void AddCard(const Card& NewCardInDeck) {
        deck.push_back(NewCardInDeck);
        CardCounter++;
    }

    Card RemoveCard(int index) {
        index--; // -1, because we started counting from 1
        Card CopyCard = deck[index];
        deck.erase(deck.begin() + index);

        MAX_CARDS--;
        CardCounter--;
        return CopyCard;
    }

    int GetCardCounter() {
        if (deck.size() > 0) {
            return CardCounter;
        }
        else {
            throw "Deck of cards is empty";
        }
    }

    void SetCardCounter(int newCardCounter) {
        this->CardCounter = newCardCounter;
    }

    void ClearDeck() {
        deck.clear();
    }
};

void AddInDeck(CardDeck& deck);  // Прототип

//class TrumpCards {
//private:
//
//public:
//
//};
//
//class SpecialCardDeck {
//private:
//    vector<TrumpCards*> deck;
//
//public:
//    void AddCard(TrumpCards* newSpecialCard) {
//        deck.push_back(newSpecialCard);
//    }
//
//    ~SpecialCardDeck() {
//        for (TrumpCards* card : deck) {
//            delete card;
//        }
//        deck.clear();
//    }
//};

class Player {
public:
    virtual void TakeCard(const Card& NewCard) = 0;
    virtual void Pass() = 0;
    virtual void Move(CardDeck& Deck) = 0;

    virtual void showCards() = 0;

    virtual int GetLife() = 0;
    virtual int GetBid() = 0;
    virtual int GetCardSum() = 0;

    virtual void SetBid(int newBid) = 0;
    virtual void SetLife(int newAlive) = 0;
    virtual void SetCardSum(int newCardSum) = 0;

    virtual void ClearArray() = 0;
};

class YourPlayer : public Player {
private:
    vector<Card> Array_of_cards;
    int CardSum = 0;
    int Bid = 1;
    int Life = 10;

    void Pass() {
        MOVE = !MOVE;
        CounterPass++;
    }

public:
    YourPlayer(){}
    YourPlayer(const Card& FirstCard, const Card& SecondCard) {
        Array_of_cards.push_back(FirstCard);
        Array_of_cards.push_back(SecondCard);

        CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();
    }

    void TakeCard(const Card& NewCard) {
        if (CardSum < winningNumber) {
            Array_of_cards.push_back(NewCard);

            CardSum += NewCard.GetNumber();
        }
        else {
            throw "You can’t take the card while you have too much";
        }
    }

    void Move(CardDeck& Deck) { 
        cout << "Your move: " << endl;
        int key;
        key = _getch();
        switch (key) {
        case Napravlenie::Two:
            try {
                TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter())));
                CounterPass = 0;
                MOVE = !MOVE;
            }
            catch (const char* error_message) {
                cout << error_message << endl;
            }
            break;
        case Napravlenie::Three:
            Pass();
            break;
        }
    }

    void showCards() {
        for (auto i : Array_of_cards) {
            i.Show();
        }
    }

    int GetCardSum() {
        return CardSum;
    }

    int GetLife() {
        return Life;
    }

    int GetBid() {
        return Bid;
    }

    void SetLife(int newLife) {
        this->Life = newLife;
    }

    void SetBid(int newBid) {
        this->Bid = newBid;
    }

    void SetCardSum(int newCardSum) {
        this->CardSum = newCardSum;
    }

    void ClearArray() {
        Array_of_cards.clear();
    }
};

class EnemyPlayer : public Player {
private:
    vector<Card> Array_of_cards;
    int CardSum = 0;
    int Bid = 1;
    int Life = 10;

    void Pass() {
        MOVE = !MOVE;
        CounterPass++;
    }

public:
    EnemyPlayer() {}
    EnemyPlayer(const Card& FirstCard, const Card& SecondCard) {
        Array_of_cards.push_back(FirstCard);
        Array_of_cards.push_back(SecondCard);
        CardSum += FirstCard.GetNumber() + SecondCard.GetNumber();
    }

    void TakeCard(const Card& NewCard) {
        Array_of_cards.push_back(NewCard);
        CardSum += NewCard.GetNumber();
    }

    void Move(CardDeck& Deck) {
        if (CardSum < 17) {
            TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter())));
            CounterPass = 0;
            MOVE = !MOVE;
        }
        else {
            Pass();
        }
    }

    void showCards() {
        for (auto i : Array_of_cards) {
            i.Show();
        }
    }

    int GetCardSum() {
        return CardSum;
    }

    int GetLife() {
        return Life;
    }

    int GetBid() {
        return Bid;
    }

    void SetLife(int newLife) {
       this->Life = newLife;
    }

    void SetBid(int newBid) {
        this->Bid = newBid;
    }

    void SetCardSum(int newCardSum) {
        this->CardSum = newCardSum;
    }

    void ClearArray() {
        Array_of_cards.clear();
    }
};

class Game {
private:
    YourPlayer player;
    EnemyPlayer enemy;
    CardDeck deck;
public:
    Game(YourPlayer& player, EnemyPlayer& enemy, CardDeck& deck) {
        this->enemy = enemy;
        this->player = player;
        this->deck = deck;
    }

    void Play() {
        do {
            Round();
            RoundResult(CheckWinner());
            RestartRound();
        } while (player.GetLife() > 0 || enemy.GetLife() > 0);

        if (player.GetLife() <= 0) {
            cout << "You lose in game";
        }
        else if (enemy.GetLife() <= 0) {
            cout << "You win in game";
        }
    }

    void Round() {
        cout << "New round" << endl;
        MOVE = random(0, 1);
        do {
            enemy.showCards();
            cout << endl << enemy.GetCardSum() << "/" << winningNumber << "\n\n";

            player.showCards();
            cout << endl << player.GetCardSum() << "/" << winningNumber << "\n\n";

            cout << "CounterPass: " << CounterPass << "\n\n\n";

            if (MOVE) {
                player.Move(deck);
            }
            else {
                enemy.Move(deck);
            }
        } while (CounterPass < 2);
    }

    int CheckWinner() {
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

    void RoundResult(int result) {
        if (result == 1) {
            player.SetLife(player.GetLife() - player.GetBid());
            enemy.SetLife(enemy.GetLife() - enemy.GetBid());
            cout << "Draw" << endl;
        }

        else if (result == 2) {
            enemy.SetLife(enemy.GetLife() - enemy.GetBid());
            cout << "You win" << endl;
        }

        else {
            player.SetLife(player.GetLife() - player.GetBid());
            cout << "You lose" << endl;
        }
    }

    void RestartRound() {
        player.SetBid(1);
        enemy.SetBid(1);

        CounterPass = 0;

        deck.ClearDeck();
        player.ClearArray();
        enemy.ClearArray();

        player.SetCardSum(0);
        enemy.SetCardSum(0);
        deck.SetCardCounter(0);

        MAX_CARDS = 11;

        AddInDeck(deck);
        for (int i = 0; i < 2; i++) {
            player.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter())));
            enemy.TakeCard(deck.RemoveCard(random(1, deck.GetCardCounter())));
        }
    }
};

void AddInDeck(CardDeck& deck) {
    for (int i = 1; i < MAX_CARDS + 1; i++) {
        deck.AddCard(Card(i));
    }
}

int main()
{
    srand(time(NULL));

    CardDeck deck;
    AddInDeck(deck);

    YourPlayer player(deck.RemoveCard(random(1, MAX_CARDS)), deck.RemoveCard(random(1, MAX_CARDS)));
    EnemyPlayer enemy(deck.RemoveCard(random(1, MAX_CARDS)), deck.RemoveCard(random(1, MAX_CARDS)));

    Game game21(player, enemy, deck);

    //Потом сделать Do While
    game21.Play();

    /*for (int i = 0;; ++i) {      Для проверки, какая клавиша под каким номером
        if (_kbhit()) {
            int key = _getch();
            cout << key << endl;
            if (key == 0x1B) break;
        }
    }*/

    /*int SecondsPassed = 0;                            Подсчет времени
    auto start = chrono::steady_clock::now();
    while (bal <= 9) {
        auto current_time = chrono::steady_clock::now();
        if (current_time - start >= chrono::seconds(1)) {
            system("cls");
            start = current_time;
            cout << "Time elapsed - " << ++SecondsPassed;
        }
    }*/
    return 0;
}