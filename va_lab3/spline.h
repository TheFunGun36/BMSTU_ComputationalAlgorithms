#ifndef SPLINE_H
#define SPLINE_H
#include "table.h"
#include "polynomial.h"

class Spline {
public:
    Spline(const Table &table, bool leftNewton = false, bool rightNewton = false);
    double value(double arg);

private:
    std::vector<Polynomial> poly;

    void generatePolynomials(const Table &table, bool leftNewton, bool rightNewton);
    void genEN(
            std::vector<double> &e,
            std::vector<double> &n,
            const std::vector<double> &y,
            const std::vector<double> &h);
    static std::vector<double> genPolynomial(
            const std::vector<double> &arg,
            std::vector<double> val);
    double genLeftC() const;
    double genRightC(
            const std::vector<double> &h,
            const std::vector<double> &y,
            double nu, double etta) const;
};

#endif // SPLINE_H
