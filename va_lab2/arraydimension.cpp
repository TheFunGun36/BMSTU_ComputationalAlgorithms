#include "arraydimension.h"
#include <cassert>

ArrayDimension::ArrayDimension(int dimension) {
    assert(dimension > 0);
    this->dimension = dimension;
}

ArrayDimension::ArrayDimension(double value) {
    dimension = 0;
    this->value = value;
}

ArrayDimension::operator double&() {
    assert(dimension == 0);
    return value;
}

ArrayDimension::operator double() const {
    assert(dimension == 0);
    return value;
}

ArrayDimension &ArrayDimension::operator[](int index) {
    return arr[index];
}

ArrayDimension ArrayDimension::operator[](int index) const {
    return arr[index];
}

void ArrayDimension::resize(size_t sz) {
    arr.resize(sz);
}

size_t ArrayDimension::size() {
    return arr.size();
}
