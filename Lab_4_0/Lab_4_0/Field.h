#pragma once
#include <vector>

class Field {
public:
    Field(int width, int height, const std::vector<int>& tiles, int zeroRow, int zeroCol);
    explicit Field(size_t size);
    void generateStartField(size_t size = 4);
    bool operator==(const Field& other) const;
    bool operator!=(const Field& other) const;

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getTile(int row, int col) const { return tiles_[row * width_ + col]; }
    void setTile(int row, int col, int value) { tiles_[row * width_ + col] = value; }
    int getZeroRow() const { return zeroRow_; }
    int getZeroCol() const { return zeroCol_; }
    void setZeroRow(int row) { zeroRow_ = row; }
    void setZeroCol(int col) { zeroCol_ = col; }

private:
    int width_;
    int height_;
    std::vector<int> tiles_;
    int zeroRow_;
    int zeroCol_;

    Field(const Field& other);
    Field& operator=(const Field& other);
};