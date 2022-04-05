#pragma once
#include "arraydimension.h"
#include <vector>

class Table {
public:
    Table(int dimesion = 2);

private:
    std::vector<std::vector<double>> args;
    ArrayDimension arr;
};
