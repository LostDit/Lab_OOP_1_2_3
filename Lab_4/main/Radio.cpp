#include "Radio.h"
#include <iostream>
#include <stdexcept>

Radio::Radio() : currentStation(0) {}

Radio::Radio(const std::vector<std::string>& st)
    : stations(st), currentStation(0) {}

void Radio::addStation(const std::string& name) {
    stations.push_back(name);
}

void Radio::showCurrent() const {
    if (stations.empty())
        std::cout << "Нет радиостанций\n";
    else
        std::cout << "Текущая станция: " << stations[currentStation] << "\n";
}

void Radio::setStation(int index) {
    if (index < stations.size())
        currentStation = index;
    else
        throw std::out_of_range("Неверный индекс станции");
}

Radio& Radio::operator++() {
    if (!stations.empty())
        currentStation = (currentStation + 1) % stations.size();
    return *this;
}

Radio& Radio::operator--() {
    if (!stations.empty())
        currentStation = (currentStation == 0) ? stations.size() - 1 : currentStation - 1;
    return *this;
}

Radio Radio::operator++(int) {
    Radio temp = *this;
    ++(*this);
    return temp;
}

Radio Radio::operator--(int) {
    Radio temp = *this;
    --(*this);
    return temp;
}