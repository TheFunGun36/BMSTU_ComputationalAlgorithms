#pragma once
#include "table.h"

class Spline {
public:
    Spline(const Table &table);

    double value(std::initializer_list<double> list);

private:
    const Table& table;
};
