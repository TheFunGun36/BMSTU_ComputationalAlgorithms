#include "coeftable.h"

CoefTable::CoefTable(int size) {
    this->size = size;
    val = new double *[size];
    for (int i = 0; i < size; i++)
        val[i] = new double[size - i + 1];
}

CoefTable::~CoefTable() {
    for (int i = 0; i < size; i++)
        delete[]val[i];
    delete[]val;
}

std::ostream &operator<<(std::ostream &os, const CoefTable &tbl) {
    if (tbl.val) {
        for (int i = 0; i < tbl.size; i++) {
            for (int j = 0; j < tbl.size - i; j++) {
                os << tbl.val[i][j] << '\t';
            }

            os << std::endl;
        }
    }
    else {
        os << "<empty>" << std::endl;
    }

    return os;
}
