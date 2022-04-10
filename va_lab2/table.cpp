#include "table.h"
#include <cassert>

Table::Table(int dimension) {
    assert(dimension > 2);
}

size_t Table::getDimension() const {
    return arr.getDimension();
}

const std::vector<double> &Table::getArgs(size_t index) const {
    return args[index];
}

const ArrayDimension &Table::getData() const {
    return arr;
}
