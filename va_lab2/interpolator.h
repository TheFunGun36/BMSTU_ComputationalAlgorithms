#pragma once
#include "table.h"

class Interpolator {
public:
    Interpolator(const Table &table, const std::vector<size_t> &powers);

    double value(std::initializer_list<double> params) const;
    double value(const std::vector<double> &params) const;

private:
    const Table& table;
    std::vector<size_t> powers;

    std::pair<size_t, size_t> closestPoints(
            const std::vector<double> &arr,
            double val,
            size_t amount) const;
    double interpolateDimension(
            const ArrayDimension &table,
            const std::vector<double> &params) const;

    static double approxValue(
            const std::pair<std::vector<double>, std::vector<double>> &data,
            double param,
            size_t power);
};
