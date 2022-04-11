#ifndef SPLINE_H
#define SPLINE_H
#include "table.h"
#include "polynomial.h"

class Spline {
public:
    Spline(const Table &table);
    double value(double arg);

private:
    const Table &table;
    std::vector<Polynomial> polynomials;

    void generatePolynomials();
    void genEN(std::vector<double> &e, std::vector<double> &n);
};

#endif // SPLINE_H
