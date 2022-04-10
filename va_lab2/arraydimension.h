#pragma once
#include <vector>

#ifdef WIN32
#include <cctype>
#endif

class ArrayDimension {
public:
    ArrayDimension(int d = 1);
    ArrayDimension(double value);

    operator double&();
    operator double() const;
    ArrayDimension &operator[](int index);
    ArrayDimension operator[](int index) const;

    inline size_t getDimension() const { return dimension; }

    void resize(size_t sz);
    size_t size();
private:
    int dimension;
    double value;
    std::vector<ArrayDimension> arr;
};
