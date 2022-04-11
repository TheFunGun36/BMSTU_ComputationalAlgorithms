#ifndef SPLINE_H
#define SPLINE_H
#include "table.h"
#include "polynomial.h"

class Spline {
public:
    Spline(const Table &table);
    double value(double arg);

private:
    std::vector<Polynomial> polynomials;

    void generatePolynomials(const Table &table);
    void genEN(std::vector<double> &e, std::vector<double> &n, const Table &table);
};

#endif // SPLINE_H
