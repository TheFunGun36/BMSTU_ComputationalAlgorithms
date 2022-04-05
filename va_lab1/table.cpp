#include "table.h"
#include <fstream>
#include <iostream>
#include <cmath>

Table::Table() {
    size = 0;
    valX = nullptr;
    valY = nullptr;
    valDeriv = nullptr;
}

Table::~Table() {
    clear();
}

Table::operator bool() const {
    return static_cast<bool>(size);
}

void Table::clear() {
    if (valX)
        delete[]valX;
    if (valY)
        delete[]valY;
    if (valDeriv)
        delete[]valDeriv;

    size = 0;
    valX = nullptr;
    valY = nullptr;
    valDeriv = nullptr;
}

void Table::duple() {
    double *buffX = new double[size << 1];
    double *buffY = new double[size << 1];
    for (int i = 0; i < size; i++) {
        int j = i << 1;
        buffX[j] = valX[i];
        buffX[j + 1] = valX[i];
        buffY[j] = valY[i];
        buffY[j + 1] = valY[i];
    }
    delete valX;
    valX = buffX;
    delete valY;
    valY = buffY;
    size <<= 1;
}

void Table::unDuple() {
    size >>= 1;
    for (int i = 1; i < size; i++) {
        int j = i << 1;
        valX[i] = valX[j];
        valY[i] = valY[j];
    }
}

int Table::findElementsAround(double centerValue, int amount) {
    if (!size)
        throw std::exception("Table don't exist");
    else if (amount > size)
        throw std::exception("Not enough elements");

    int closest = 0;
    double bestDistance = abs(centerValue - valX[0]);
    double curDistance = bestDistance;

    for (int i = 0; i < size && curDistance <= bestDistance; i++) {
        curDistance = abs(centerValue - valX[i]);

        if (curDistance < bestDistance) {
            bestDistance = curDistance;
            closest = i;
        }
    }

    int start = closest - amount / 2 + (centerValue > valX[0] && amount % 2 == 0);
    start = start < 0 ? 0 : start;
    start = start + amount >= size ? size - amount : start;

    return start;
}

bool Table::loadFromFile(std::string filename) {
    bool rc = false;
    std::ifstream in(filename);

    if (in.is_open()) {
        int nsize;
        if (in >> nsize) {
            double *nvalX = new double[nsize];
            double *nvalY = new double[nsize];
            double *nvalDeriv = new double[nsize];

            rc = true;
            for (int i = 0; i < nsize && rc; i++) {
                rc &= static_cast<bool>(in >> nvalX[i]);
                rc &= static_cast<bool>(in >> nvalY[i]);
                rc &= static_cast<bool>(in >> nvalDeriv[i]);
            }

            if (rc) {
                clear();
                size = nsize;
                valX = nvalX;
                valY = nvalY;
                valDeriv = nvalDeriv;
            }
        }

        in.close();
    }

    return rc;
}

void Table::cutElementsAround(double centerValue, int amount) {
    int start = findElementsAround(centerValue, amount);
    
    for (int i = 0; i < amount; i++) {
        valX[i] = valX[i + start];
        valY[i] = valY[i + start];
        valDeriv[i] = valDeriv[i + start];
    }

    size = amount;
}

void Table::swapXY() {
    std::swap(valX, valY);
}

std::ostream &operator<<(std::ostream &os, const Table &tbl) {
    if (tbl.size) {
        os << "x\ty\tderiv" << std::endl;
        for (int i = 0; i < tbl.size; i++) {
            os << tbl.valX[i] << '\t' << tbl.valY[i] << '\t' << tbl.valDeriv[i] << std::endl;
        }
    }
    else {
        os << "<empty>" << std::endl;
    }

    return os;
}
