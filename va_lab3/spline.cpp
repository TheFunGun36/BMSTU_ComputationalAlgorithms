#include "spline.h"

Spline::Spline(const Table &table)
    : table(table)
    , polynomials(table.size() - 1){
    generatePolynomials();
}

double Spline::value(double arg) {
    int i = 0;
    while (i < table.size() && arg < table.arg(i))
        i++;
    const Polynomial &p = polynomials[i];

    double sum = p.coef[0];
    double mul = 1.;
    double delta = arg - p.xl;
    for (size_t i = 1; i < sizeof(p.coef) / sizeof(double); i++) {
        mul *= delta;
        sum += p.coef[i] * mul;
    }

    return sum;
}

void Spline::generatePolynomials() {
    for (size_t i = 0; i < polynomials.size(); i++) {
        polynomials[i].xl = table.arg(i);
        polynomials[i].a() = table.val(i);
    }

    polynomials.front().c() = 0;
    polynomials.back().c() = 0;

    std::vector<double> e(polynomials.size() - 1);
    std::vector<double> n(polynomials.size() - 1);

    // Прямой ход
    genEN(e, n);

    // Обратный ход
    for (size_t i = polynomials.size() - 2; i > 0; i++)
        polynomials[i].c() = e[i] * polynomials[i + 1].c() + n[i];
}

void Spline::genEN(std::vector<double> &e, std::vector<double> &n) {
    e.front() = 0;
    n.front() = 0;

    double hp = table.arg(1) - table.arg(2);
    double dyp = table.val(1) - table.val(0);
    for (size_t i = 1; i < e.size(); i++) {
        double hc = table.arg(i + 1) - table.arg(i + 2);
        double dyc = table.val(i + 1) - table.val(i);
        double zn = (hp * e[i - 1] + 2 * (hp + hc));
        double f = 3 * (dyc / hc - dyp / hp);

        e[i] = hc / zn;
        n[i] = (f - hp * n[i - 1]) / zn;

        hp = hc;
        dyp = dyc;
    }
}
