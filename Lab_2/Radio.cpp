#include "Radio.h"

Radio::Radio() : volume(5), station(1) {}

unsigned int Radio::getVolume() const { return volume; }
unsigned int Radio::getStation() const { return station; }

void Radio::setVolume(unsigned int const & vol) {
    if (vol >= MIN_VOLUME && vol <= MAX_VOLUME) volume = vol;
}

void Radio::setStation(unsigned int const & st) {
    if (st >= MIN_STATION && st <= MAX_STATION) station = st;
}

void Radio::incVolume() {
    if (volume < MAX_VOLUME) ++volume;
}

void Radio::decVolume() {
    if (volume > MIN_VOLUME) --volume;
}

void Radio::nextStation() {
    if (station == MAX_STATION) station = MIN_STATION;
    else ++station;
}

void Radio::previousStation() {
    if (station == MIN_STATION) station = MAX_STATION;
    else --station;
}