#ifndef FIFTEEN_HPP
#define FIFTEEN_HPP

#include "Field.h"

class Fifteen {
private:
    Field game_field;
    int count;

    // Запрет копирования и присваивания
    Fifteen(const Fifteen&);
    Fifteen& operator=(const Fifteen&);

public:
    explicit Fifteen(int size);
    ~Fifteen() = default;

    int getCount() const;
    void run();
    void draw() const;
    bool isGameOver() const;
    void onKeyPressed(const int& btnCode);
};

#endif