#include "Field.h"

Field::Field(size_t const & sz) : size(sz), field(sz * sz), zeroIndex(sz * sz - 1) {
    for (size_t i = 0; i < field.size() - 1; ++i) {
        field[i] = static_cast<int>(i + 1);
    }
    field.back() = 0;
}

size_t Field::getSize() const { return size; }
const std::vector<int>& Field::getField() const { return field; }
size_t Field::getZeroIndex() const { return zeroIndex; }

void Field::shiftUp() {
    if (zeroIndex >= size) {
        std::swap(field[zeroIndex], field[zeroIndex - size]);
        zeroIndex -= size;
    }
}

void Field::shiftDown() {
    if (zeroIndex < size * (size - 1)) {
        std::swap(field[zeroIndex], field[zeroIndex + size]);
        zeroIndex += size;
    }
}

void Field::shiftLeft() {
    if (zeroIndex % size != 0) {
        std::swap(field[zeroIndex], field[zeroIndex - 1]);
        --zeroIndex;
    }
}

void Field::shiftRight() {
    if (zeroIndex % size != size - 1) {
        std::swap(field[zeroIndex], field[zeroIndex + 1]);
        ++zeroIndex;
    }
}