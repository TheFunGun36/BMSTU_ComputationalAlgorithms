#pragma once
#include "arraydimension.h"
#include <vector>

class Table {
public:
    Table(int dimesion = 2);

    size_t dimension() const;

private:
    std::vector<std::vector<double>> args;
    ArrayDimension arr;
};
