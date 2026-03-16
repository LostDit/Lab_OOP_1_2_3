#ifndef RADIO_HPP
#define RADIO_HPP

#include <vector>
#include <string>

class Radio {
private:
    std::vector<std::string> stations;
    size_t currentStation;

public:
    Radio();
    explicit Radio(const std::vector<std::string>& st);
    Radio(const Radio&) = default;
    Radio& operator=(const Radio&) = default;
    ~Radio() = default;

    void addStation(const std::string& name);
    void showCurrent() const;
    void setStation(size_t index);

    // Префиксные операторы
    Radio& operator++();      // следующая станция
    Radio& operator--();      // предыдущая станция

    // Постфиксные операторы
    Radio operator++(int);
    Radio operator--(int);
};

#endif