#include "Fifteen.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Fifteen::Fifteen(size_t size)
    : game_field(size), count(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Fifteen::~Fifteen() {}

void Fifteen::run() {
    shuffleField();
    count = 0;
}

void Fifteen::shuffleField() {
    for (int step = 0; step < 1000; ++step) {
        int dir = std::rand() % 4;
        int dr = 0, dc = 0;
        switch (dir) {
        case 0: dr = -1; break;
        case 1: dr = 1; break;
        case 2: dc = -1; break;
        case 3: dc = 1; break;
        }
        if (canMove(dr, dc))
            moveZero(dr, dc);
    }
}

bool Fifteen::canMove(int deltaRow, int deltaCol) const {
    int newRow = game_field.getZeroRow() + deltaRow;
    int newCol = game_field.getZeroCol() + deltaCol;
    return newRow >= 0 && newRow < game_field.getHeight() &&
        newCol >= 0 && newCol < game_field.getWidth();
}

void Fifteen::moveZero(int deltaRow, int deltaCol) {
    int zr = game_field.getZeroRow();
    int zc = game_field.getZeroCol();
    int tr = zr + deltaRow;
    int tc = zc + deltaCol;
    if (!canMove(deltaRow, deltaCol))
        return;
    int val = game_field.getTile(tr, tc);
    game_field.setTile(zr, zc, val);
    game_field.setTile(tr, tc, 0);
    game_field.setZeroRow(tr);
    game_field.setZeroCol(tc);
    ++count;
}

void Fifteen::draw() const {
    int w = game_field.getWidth();
    int h = game_field.getHeight();
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            int val = game_field.getTile(row, col);
            if (val == 0)
                std::cout << "   ";
            else
                std::cout << (val < 10 ? " " : "") << val << " ";
        }
        std::cout << std::endl;
    }
}

bool Fifteen::isGameOver() const {
    Field correct(static_cast<size_t>(game_field.getWidth()));
    return game_field == correct;
}

void Fifteen::onKeyPressed(int btnCode) {
    switch (btnCode) {
    case 72: moveZero(-1, 0); break;
    case 80: moveZero(1, 0); break;
    case 75: moveZero(0, -1); break;
    case 77: moveZero(0, 1); break;
    }
}

int Fifteen::getCount() const {
    return count;
}