#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h> 
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
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

bool MOVE = true; // true - your move, false - enemy move
int WhoWin = 0; // 1 - you, 2 - enemy, 3 - draw
int CounterPass = 0; // if 2 -  opening of closed cards
const int MAX_CARDS = 11;

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
    int GetNumber() {
        return number;
    }
    void Show() {
        cout << "Number: " << number << endl;
    }
};

class SpecialCard {
private:

public:

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

        for (auto i : deck) {
            i.Show();
        }
        cout << endl;

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
};

class SpecialCardDeck {
private:
    vector<SpecialCard*> deck;

public:
    void AddCard(SpecialCard* newSpecialCard) {
        deck.push_back(newSpecialCard);
    }

    ~SpecialCardDeck() {
        for (SpecialCard* card : deck) {
            delete card;
        }
        deck.clear();
    }
};

class Player {
private:
    vector<Card> Array_of_cards;
    int PlayerCardCounter = 0;
    int Bid = 1;
    int Alive = 10;

    void TakeCard(const Card& NewCard) {
        PlayerCardCounter++;
        Array_of_cards.push_back(NewCard);
    }

    void Pass() {
        MOVE = false;
        CounterPass++;
    }
public:
    Player(const Card& FirstCard, const Card& SecondCard) {
        Array_of_cards.push_back(FirstCard);
        Array_of_cards.push_back(SecondCard);
        PlayerCardCounter += 2;
    }

    void Move(CardDeck& Deck) {
        do {
            cout << "Your move: " << endl;
            int key;
            key = _getch();
            switch (key) {
            case Two:
                TakeCard(Deck.RemoveCard(random(1, Deck.GetCardCounter())));
                break;
            case Three:
                Pass();
                break;
            }
        } while (MOVE);
    }

    void ShowInfo() {
        for (auto i : Array_of_cards) {
            i.Show();
        }
    }
};

class Game {
private:

public:

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

    Player player(deck.RemoveCard(random(1, MAX_CARDS)), deck.RemoveCard(random(1, MAX_CARDS)));

    try {
        player.Move(deck);
    }
    catch (const char* error_message) {
        cout << error_message << endl;
    }

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
}