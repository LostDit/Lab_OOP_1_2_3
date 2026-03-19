#ifndef FIELD_HPP
#define FIELD_HPP

#include <cstddef>
#include <vector>

class Field {
private:
    int size;
    std::vector<std::vector<int>> field;
    int zeroRow;
    int zeroCol;

    Field(const Field&);

public:
    explicit Field(int s);
    ~Field() = default;

    void generateStartField(const int& s);

    int getCell(int r, int c) const;
    bool isEqualTo(const Field& other) const;
    bool moveZero(int dr, int dc);
    
    int getSize() const;
};
#endif