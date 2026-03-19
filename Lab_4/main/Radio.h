#ifndef RADIO_HPP
#define RADIO_HPP

#include <vector>
#include <string>

class Radio {
private:
    std::vector<std::string> stations;
    int currentStation;

public:
    Radio();
    explicit Radio(const std::vector<std::string>& st);
    Radio(const Radio&) = default;
    Radio& operator=(const Radio&) = default;
    ~Radio() = default;

    void addStation(const std::string& name);
    void showCurrent() const;
    void setStation(int index);

    // Префиксные операторы
    Radio& operator++();      // следующая станция
    Radio& operator--();      // предыдущая станция

    // Постфиксные операторы
    Radio operator++(int);
    Radio operator--(int);
};

#endif