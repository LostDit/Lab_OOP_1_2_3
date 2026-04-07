#include "Radio.h"

Radio::Radio() : station_(MIN_STATION) {}

Radio& Radio::operator++() {
    if (station_ == MAX_STATION)
        station_ = MIN_STATION;
    else
        ++station_;
    return *this;
}

Radio Radio::operator++(int) {
    Radio temp = *this;
    ++(*this);
    return temp;
}

Radio& Radio::operator--() {
    if (station_ == MIN_STATION)
        station_ = MAX_STATION;
    else
        --station_;
    return *this;
}

Radio Radio::operator--(int) {
    Radio temp = *this;
    --(*this);
    return temp;
}

int Radio::getStation() const {
    return station_;
}