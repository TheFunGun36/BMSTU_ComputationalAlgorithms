#pragma once
#include <iostream>

class CoefTable {
public:
    CoefTable(int size);
    ~CoefTable();

    inline int getSize() {
        return size;
    }

    inline double getVal(int i, int j) {
        return val[i][j];
    }

    inline void setVal(int i, int j, double val) {
        this->val[i][j] = val;
    }

    friend std::ostream &operator<<(std::ostream &os, const CoefTable &tbl);

private:
    int size;
    double **val;
};
