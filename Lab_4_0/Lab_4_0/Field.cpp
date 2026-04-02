#include "Field.h"

Field::Field(int width, int height, const std::vector<int>& tiles, int zeroRow, int zeroCol)
    : width_(width), height_(height), tiles_(tiles), zeroRow_(zeroRow), zeroCol_(zeroCol) {
}

bool Field::operator==(const Field& other) const {
    if (width_ != other.width_ || height_ != other.height_) return false;
    if (zeroRow_ != other.zeroRow_ || zeroCol_ != other.zeroCol_) return false;
    return tiles_ == other.tiles_;
}

bool Field::operator!=(const Field& other) const {
    return !(*this == other);
}