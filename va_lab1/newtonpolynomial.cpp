#include "newtonpolynomial.h"

Polynomial::Polynomial(const Table &table)
    : coefTable(table.getSize()) {
    xarr = new double[table.getSize()];
    power = table.getSize() - 1;

    this->compile(table);
}

Polynomial::~Polynomial() {
    if (xarr)
        delete[]xarr;

    power = 0;
    xarr = nullptr;
}

double Polynomial::calculate(double arg) {
    double result = coefTable.getVal(0, 0);
    double mulArg = 1;

    for (int i = 1; i <= power; i++) {
        mulArg *= (arg - xarr[i - 1]);
        result += coefTable.getVal(0, i) * mulArg;
    }

    return result;
}

void Polynomial::getTableStream(std::ostream &os) {
    os << coefTable;
}

void Polynomial::compile(const Table &table) {
    for (int i = 0; i < table.getSize(); i++)
        coefTable.setVal(i, 0, table.getY(i));

    for (int i = 0; i < table.getSize(); i++)
        xarr[i] = table.getX(i);

    // Обходим каждый столбец таблицы разделённых разностей
    for (int i = 0; i < power + 1; i++) {

        // Считаем каждый узел
        for (int j = 0; j < power - i; j++) {
            double x1 = xarr[j];
            double x2 = xarr[j + i + 1];
            double v = 0;

            // В подставляем производную, если x равны
            if (isEqual(x1, x2)) {
                v = table.getDeriv(j >> 1);
            }
            else {
                double f1 = coefTable.getVal(j, i);
                double f2 = coefTable.getVal(j + 1, i);
                v = (f1 - f2) / (x1 - x2);
            }

            coefTable.setVal(j, i + 1, v);
        }
    }
}

bool Polynomial::isEqual(double a, double b) const {
    return abs(a - b) < eps;
}
