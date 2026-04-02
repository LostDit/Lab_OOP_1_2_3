#pragma once
#include <vector>

class Field {
public:
    Field(int width, int height, const std::vector<int>& tiles, int zeroRow, int zeroCol);
    bool operator==(const Field& other) const;
    bool operator!=(const Field& other) const;
private:
    int width_;
    int height_;
    std::vector<int> tiles_;
    int zeroRow_;
    int zeroCol_;
};