#ifndef FIELD_HPP
#define FIELD_HPP

#include <cstddef>
#include <vector>

class Field {
private:
    size_t size;
    std::vector<std::vector<int>> field;
    int zeroRow;
    int zeroCol;

    // Запрет копирования и присваивания
    Field(const Field&);
    Field& operator=(const Field&);

public:
    explicit Field(size_t s);
    ~Field() = default;

    void generateStartField(const size_t& s);
    bool operator==(const Field& lhs, const Field& rhs);
    bool operator!=(const Field& lhs, const Field& rhs);

    int getCell(int r, int c) const;
    bool isEqualTo(const Field& other) const;
    bool moveZero(int dr, int dc);
    size_t getSize() const;
};

#endif