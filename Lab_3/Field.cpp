#include "Field.h"
#include <algorithm>
#include <stdexcept>

Field::Field(size_t s) : size(s), field(s, std::vector<int>(s)) {
    if (s == 0)
        throw std::invalid_argument("Field size cannot be zero");
    generateStartField(s);
}

void Field::generateStartField(const size_t& s) {
    if (s == 0) return;
    int value = 1;
    for (size_t i = 0; i < s; ++i) {
        for (size_t j = 0; j < s; ++j) {
            field[i][j] = value++;
        }
    }
    field[s - 1][s - 1] = 0;
    zeroRow = static_cast<int>(s - 1);
    zeroCol = static_cast<int>(s - 1);
}

int Field::getCell(int r, int c) const {
    return field[r][c];
}

bool Field::isEqualTo(const Field& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            if (field[i][j] != other.field[i][j])
                return false;
    return true;
}

bool Field::moveZero(int dr, int dc) {
    int newRow = zeroRow + dr;
    int newCol = zeroCol + dc;
    if (newRow < 0 || newRow >= static_cast<int>(size) ||
        newCol < 0 || newCol >= static_cast<int>(size))
        return false;
    std::swap(field[zeroRow][zeroCol], field[newRow][newCol]);
    zeroRow = newRow;
    zeroCol = newCol;
    return true;
}

size_t Field::getSize() const {
    return size;
}