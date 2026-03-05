#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Field {
private:
    size_t size;
    std::vector<int> field;
    size_t zeroIndex;

public:
    Field(size_t const & sz = 4);
    size_t getSize() const;
    const std::vector<int>& getField() const;
    size_t getZeroIndex() const;
    void shiftUp();
    void shiftDown();
    void shiftLeft();
    void shiftRight();
};

#endif // FIELD_H