#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


struct Polynomial {
    inline double &a() { return coef[0]; }
    inline double &b() { return coef[1]; }
    inline double &c() { return coef[2]; }
    inline double &d() { return coef[3]; }
    inline double a() const { return coef[0]; }
    inline double b() const { return coef[1]; }
    inline double c() const { return coef[2]; }
    inline double d() const { return coef[3]; }
    double coef[4];
    double xl;
    double xr;
};

#endif // POLYNOMIAL_H
