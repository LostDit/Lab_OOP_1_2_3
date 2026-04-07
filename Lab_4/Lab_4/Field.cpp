#include "Field.h"

Field::Field(int width, int height, const std::vector<int>& tiles, int zeroRow, int zeroCol)
    : width_(width), height_(height), tiles_(tiles), zeroRow_(zeroRow), zeroCol_(zeroCol) {
}

Field::Field(size_t size)
    : width_(static_cast<int>(size)), height_(static_cast<int>(size)),
    tiles_(size* size, 0), zeroRow_(static_cast<int>(size) - 1), zeroCol_(static_cast<int>(size) - 1) {
    generateStartField(size);
}

void Field::generateStartField(size_t size) {
    if (size != static_cast<size_t>(width_) || size != static_cast<size_t>(height_)) {
        width_ = height_ = static_cast<int>(size);
        tiles_.resize(size * size);
    }
    for (size_t i = 0; i < size * size - 1; ++i)
        tiles_[i] = static_cast<int>(i + 1);
    tiles_[size * size - 1] = 0;
    zeroRow_ = static_cast<int>(size) - 1;
    zeroCol_ = static_cast<int>(size) - 1;
}

bool Field::operator==(const Field& other) const {
    if (width_ != other.width_ || height_ != other.height_) return false;
    if (zeroRow_ != other.zeroRow_ || zeroCol_ != other.zeroCol_) return false;
    return tiles_ == other.tiles_;
}

bool Field::operator!=(const Field& other) const {
    return !(*this == other);
}