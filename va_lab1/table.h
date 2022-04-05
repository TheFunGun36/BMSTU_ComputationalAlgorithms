#pragma once
#include <vector>
#include <string>
#include <exception>

class Table {
public:
    Table();
    ~Table();

    bool loadFromFile(std::string filename);
    void cutElementsAround(double centerValue, int amount);
    void swapXY();
    void clear();
    void duple();
    void unDuple();

    inline double getX(int idx) const {
        return valX[idx];
    }

    inline double getY(int idx) const {
        return valY[idx];
    }

    inline double getDeriv(int idx) const {
        return valDeriv[idx];
    }

    inline bool exists(int idx) const {
        return idx < size;
    }

    inline int getSize() const {
        return size;
    }

    operator bool() const;
    friend std::ostream &operator<<(std::ostream &os, const Table &tbl);
private:
    int findElementsAround(double centerValue, int amount);
    int size;
    double *valX;
    double *valY;
    double *valDeriv;
};

