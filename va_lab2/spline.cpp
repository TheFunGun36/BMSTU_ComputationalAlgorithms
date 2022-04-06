#include "spline.h"
#include <cassert>

Spline::Spline(const Table &table)
    : table(table) {

}

double Spline::value(std::initializer_list<double> list) {
    assert(table.dimension() == list.size());

}
