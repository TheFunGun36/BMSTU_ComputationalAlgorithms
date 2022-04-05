#pragma once
#include <vector>

class ArrayDimension {
public:
    ArrayDimension(int d = 1);
    ArrayDimension(double value);

    operator double&();
    ArrayDimension &operator[](int index);

    void resize(size_t sz);
    size_t size();
private:
    int dimension;
    double value;
    std::vector<ArrayDimension> arr;
};
