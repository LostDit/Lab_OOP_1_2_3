#ifndef RADIO_H
#define RADIO_H

class Radio {
private:
    unsigned int volume;
    unsigned int station;
    const unsigned int MIN_VOLUME = 0;
    const unsigned int MAX_VOLUME = 10;
    const unsigned int MIN_STATION = 1;
    const unsigned int MAX_STATION = 10;

public:
    Radio();
    [[nodiscard]] unsigned int getVolume() const;
    [[nodiscard]] unsigned int getStation() const;
    void setVolume(unsigned int const & vol);
    void setStation(unsigned int const & st);
    void incVolume();
    void decVolume();
    void nextStation();
    void previousStation();
};

#endif // RADIO_H