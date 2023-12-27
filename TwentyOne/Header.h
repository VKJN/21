#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <conio.h> 
#include <SFML/Graphics.hpp>
#include <chrono>
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