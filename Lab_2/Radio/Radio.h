#pragma once

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
    unsigned int getVolume() const;
    unsigned int getStation() const;
    void setVolume(unsigned int const& volume);
    void setStation(unsigned int const& station);

    void incVolume();
    void decVolume();
    void nextStation();
    void previousStation();
};