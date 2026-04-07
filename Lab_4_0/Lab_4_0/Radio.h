#pragma once
#include <iostream>

class Radio {
public:
    Radio();
    Radio& operator++();
    Radio& operator--();
    Radio operator++(int);
    Radio operator--(int);
    int getStation() const;
private:
    int station_;
    static const int MIN_STATION = 0;
    static const int MAX_STATION = 9;
};