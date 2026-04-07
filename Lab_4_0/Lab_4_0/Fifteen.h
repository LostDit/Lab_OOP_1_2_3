#pragma once
#include "Field.h"

class Fifteen {
public:
    explicit Fifteen(size_t size);
    ~Fifteen();

    void run();
    void draw() const;
    bool isGameOver() const;
    void onKeyPressed(int btnCode);
    int getCount() const;

private:
    Field game_field;
    int count;

    Fifteen(const Fifteen&);
    Fifteen& operator=(const Fifteen&);

    void shuffleField();
    bool canMove(int deltaRow, int deltaCol) const;
    void moveZero(int deltaRow, int deltaCol);
};