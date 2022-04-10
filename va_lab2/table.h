#pragma once
#include "arraydimension.h"
#include <vector>

class Table {
public:
    Table(int dimesion = 2);

    size_t getDimension() const;
    const std::vector<double> &getArgs(size_t index) const;
    const ArrayDimension &getData() const;

private:
    std::vector<std::vector<double>> args;
    ArrayDimension arr;
};
