#ifndef FIFTEEN_H
#define FIFTEEN_H

#include "Field.h"

class Fifteen {
private:
    Field game_field;
    int count;

    // Запрет копирования и присваивания
    Fifteen(const Fifteen&);
    Fifteen& operator=(const Fifteen&);

public:
    explicit Fifteen(size_t size);
    ~Fifteen() = default;

    int getCount() const;
    void run();
    void draw() const;
    bool isGameOver() const;
    void onKeyPressed(const int& btnCode);
};

#endif