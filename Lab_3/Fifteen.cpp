#include "Fifteen.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

Fifteen::Fifteen(size_t size) : game_field(size), count(0) {}


void Fifteen::run() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < 1000; ++i) {
        int dir = std::rand() % 4;
        int dr = 0, dc = 0;
        switch (dir) {
        case 0: dr = -1; break;
        case 1: dr = 1; break;
        case 2: dc = -1; break;
        case 3: dc = 1; break;
        }
        game_field.moveZero(dr, dc);
    }
    count = 0;
}

void Fifteen::draw() const {
    size_t sz = game_field.getSize();
    int maxNumber = static_cast<int>(sz * sz - 1);
    int width = 1;
    while (maxNumber >= 10) {
        ++width;
        maxNumber /= 10;
    }

    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            std::cout << std::setw(width) << game_field.getCell(i, j);
            if (j < sz - 1) std::cout << ' ';  // пробел между числами
        }
        std::cout << '\n';
    }
}

bool Fifteen::isGameOver() const {
    Field tmp(game_field.getSize());
    return game_field.isEqualTo(tmp);
}

void Fifteen::onKeyPressed(const int& btnCode) {
    int dr = 0, dc = 0;
    switch (btnCode) {
    case 72: dr = -1; break;
    case 80: dr = 1; break;
    case 75: dc = -1; break;
    case 77: dc = 1; break;
    default: return;
    }
    if (game_field.moveZero(dr, dc)) {
        ++count;
    }
}