#include "spline.h"
#include <cassert>

Spline::Spline(const Table &table, bool leftNewton, bool rightNewton)
    : poly(table.size() - 1) {
    generatePolynomials(table, leftNewton, rightNewton);
}

double Spline::value(double arg) {
    size_t i = 0;
    while (i < poly.size() - 1 && arg >= poly[i + 1].xl)
        i++;
    const Polynomial &p = poly[i];

    double sum = p.coef[0];
    double mul = 1.;
    double delta = arg - p.xl;
    for (size_t i = 1; i < sizeof(p.coef) / sizeof(double); i++) {
        mul *= delta;
        sum += p.coef[i] * mul;
    }

    return sum;
}

void Spline::generatePolynomials(const Table &table, bool leftNewton, bool rightNewton) {
    std::vector<double> h(poly.size() + 1);
    std::vector<double> y(poly.size() + 1);

    // Сразу находим коэффициенты а
    for (size_t i = 0; i < poly.size(); i++) {
        poly[i].xl = table.arg(i);
        poly[i].xr = table.arg(i + 1);
        poly[i].a() = table.val(i);
        h[i] = table.arg(i + 1) - table.arg(i);
        y[i] = table.val(i);
    }

    y.back() = table.val(y.size() - 1);
    h.back() = poly.back().xr - poly.back().xl;

    // Находим коэффициенты c
    poly.front().c() = leftNewton ? genLeftC() : 0.;

    std::vector<double> e(poly.size() + 1);
    std::vector<double> n(poly.size() + 1);

    // Прямой ход
    genEN(e, n, y, h);

    // Обратный ход
    double rightC = rightNewton ? genRightC(h, y, n.back(), e.back()) : 0.;

    poly.back().c() = e.back() * rightC + n.back();

    for (int i = poly.size() - 2; i > 0; i--)
        poly[i].c() = e[i + 1] * poly[i + 1].c() + n[i + 1];

    // Определяем оставшиеся коэффициенты
    for (size_t i = 0; i < poly.size() - 1; i++) {
        poly[i].b() = (y[i + 1] - y[i]) / h[i] - h[i] * (poly[i + 1].c() + 2. * poly[i].c()) / 3.;
        poly[i].d() = (poly[i + 1].c() - poly[i].c()) / (3. * h[i]);
    }

    {
        size_t i = poly.size() - 1;
        poly[i].b() = (y[i + 1] - y[i]) / h[i] - h[i] * 2. * poly[i].c() / 3.;
        poly[i].d() = -poly[i].c() / (3. * h[i]);
    }
}

void Spline::genEN(
        std::vector<double> &e,
        std::vector<double> &n,
        const std::vector<double> &y,
        const std::vector<double> &h) {
    e[0] = 0;
    n[0] = 0;
    e[1] = 0;
    n[1] = poly.front().c();

    for (size_t i = 1; i < e.size() - 1; i++) {
        double zn = h[i - 1] * e[i] + 2 * (h[i - 1] + h[i]);
        e[i + 1] = -h[i] / zn;
        double f = 3 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);
        n[i + 1] = (f - h[i - 1] * n[i]) / zn;
    }
}

std::vector<double> Spline::genPolynomial(
        const std::vector<double> &arg,
        std::vector<double> val) {
    std::vector<double> valNew(val.size() - 1);
    std::vector<double> result(val.size());

    result[0] = val[0];

    for (size_t i = 0; i < arg.size() - 1; i++) {
        for (size_t j = 0; j < arg.size() - i - 1; j++) {
            assert (j + i + 1 < arg.size());
            double arg1 = arg[j];
            double arg2 = arg[j + i + 1];

            double f1 = val[j];
            assert(j + 1 < val.size());
            double f2 = val[j + 1];
            double f = (f1 - f2) / (arg1 - arg2);
            valNew[j] = f;
        }

        std::swap(val, valNew);
        result[i + 1] = val[0];
    }

    return result;
}

double Spline::genLeftC() const {
    std::vector<double> args(4);
    std::vector<double> vals(4);
    for (int i = 0; i < 4; i++) {
        args[i] = poly[i].xl;
        vals[i] = poly[i].a();
    }
    std::vector<double> p = genPolynomial(args, vals);

    //2c + d(6x - 2(x1 + x2 + x3))
    //return p[2] * 2 + p[3] * (6 * args[0] - 2 * (args[0] + args[1] + args[2]));
    //d = p[3] * (6 * args[0] - 2 * (args[0] + args[1] + args[2]));
    //return p[2] * 2;
    return 2. * (p[2] + p[3] * (2. * args[0] - args[1] - args[2]));
}

double Spline::genRightC(
        const std::vector<double> &h,
        const std::vector<double> &y,
        double nu, double etta) const {
    std::vector<double> args(4);
    std::vector<double> vals(4);

    size_t n = h.size() - 1;
    for (size_t i = 0; i < 4; i++) {
        assert(n + 1 - 4 < poly.size());
        assert(n + i - 3 < y.size());
        args[i] = poly[n + i - 4].xr;
        vals[i] = y[n + i - 3];
    }
    std::vector<double> p = genPolynomial(args, vals);

    //2c + d(6x - 2(x1 + x2 + x3))
    double pVal = p[2] * 2 + p[3] * (6 * args[3] - 2 * (args[0] + args[1] + args[2]));
    double alpha = h[n] * h[n - 1] / 3.;
    double beta = 2. / 3. * h[n] * (h[n - 1] + h[n]);
    double gamma = y[n] - y[n - 1] + (y[n - 2] - y[n - 1]) * h[n] / h[n - 1] - pVal * h[n] * h[n] / 6.;
    return (gamma - alpha * nu) / (alpha * etta + beta);
}
