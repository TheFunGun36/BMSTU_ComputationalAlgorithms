#pragma once
#include "table.h"
#include <iostream>
#include "coeftable.h"

class Polynomial {
public:
    Polynomial(const Table &table);
    ~Polynomial();
    double calculate(double arg);
    void getTableStream(std::ostream &os);

private:
    CoefTable coefTable;
    int power;
    double *xarr;
    double eps;

    void compile(const Table &table);
    bool isEqual(double a, double b) const;
};

