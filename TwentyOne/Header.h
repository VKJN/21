#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h> 
#include <chrono>
#define random(a,b) (a+rand()%(b+1-a))

extern bool MOVE; // true - your move, false - enemy move
extern int CounterPass; // if 2 - opening of closed cards
extern int MAX_CARDS;
extern int winningNumber;

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