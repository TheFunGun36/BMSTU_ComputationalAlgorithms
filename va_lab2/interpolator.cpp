#include "interpolator.h"
#include <cassert>

Interpolator::Interpolator(const Table &table, const std::vector<size_t> &powers)
    : table(table),
    powers(powers) {
    assert(powers.size() == table.getDimension());
}

double Interpolator::value(std::initializer_list<double> params) const {
    return value(std::vector<double>(params));
}

double Interpolator::value(const std::vector<double> &params) const {
    assert(table.getDimension() == params.size());
    return interpolateDimension(table.getData(), params);
}

double Interpolator::interpolateDimension(
        const ArrayDimension &tableData,
        const std::vector<double> &params) const {
    if (tableData.getDimension() == 0)
        return tableData;

    size_t level = table.getDimension() - tableData.getDimension();

    auto range = closestPoints(table.getArgs(level), params[level], powers[level] + 1);

    std::vector<double> arg(range.second - range.first);
    std::vector<double> val(range.second - range.first);

    auto itval = val.begin();
    auto itarg = arg.begin();
    for (size_t i = range.first; i < range.second; i++, itarg++, itval++) {
        *itarg = table.getArgs(level)[i];
        *itval = interpolateDimension(tableData[i], params);
    }

    std::vector<double> polynomial = genPolynomial(arg, val);
    return calcValue(arg, polynomial, params[level]);
}

std::pair<size_t, size_t> Interpolator::closestPoints(
        const std::vector<double> &arr,
        double val,
        size_t amount) const {
    if (amount > arr.size())
        throw "Слишком большая степень полинома";
    else if (val < arr.front() || val > arr.back())
        throw "Экстраполяция недопустима";

    int c = 0;
    while (c < int(arr.size()) && arr[c] < val)
        c++;

    int amountHalf = amount / 2;
    int amountRemainder = amount % 2;
    auto result = std::make_pair(c - amountHalf, c + amountHalf + amountRemainder);
    // Examples:
    //     0   1  [2]  3   4   5   6
    //           ^
    //             1   1
    //         2       2
    //         3           3
    //     4               4
    //     5                   5

    if (result.first < 0) {
        result.second -= result.first;
        result.first = 0;
    }
    else if (result.second > int(arr.size())) {
        size_t shift = result.second - arr.size() + 1;
        result.first -= shift;
        result.second -= shift;
    }

    return result;
}

std::vector<double> Interpolator::genPolynomial(
        const std::vector<double> &arg,
        std::vector<double> val) {
    assert(arg.size() == val.size());
    std::vector<double> valNew(val.size() - 1);
    std::vector<double> result(val.size());

    result[0] = val[0];

    for (size_t i = 0; i < arg.size() - 1; i++) {
        for (size_t j = 0; j < arg.size() - i - 1; j++) {
            double arg1 = arg[j];
            double arg2 = arg[j + i + 1];
            assert(!fuzzyEq(arg1, arg2));

            double f1 = val[j];
            double f2 = val[j + 1];
            double f = (f1 - f2) / (arg1 - arg2);
            valNew[j] = f;
        }

        std::swap(val, valNew);
        result[i + 1] = val[0];
    }

    return result;
}

bool Interpolator::fuzzyEq(double a, double b) {
    return abs(a - b) <= 1e-10;
}

double Interpolator::calcValue(
        const std::vector<double> &args,
        const std::vector<double> &polynomial,
        double arg) {
    assert(polynomial.size() > 0);
    double result = polynomial[0];
    double mulArg = 1;

    for (size_t i = 1; i < polynomial.size(); i++) {
        mulArg *= (arg - args[i - 1]);
        result += polynomial[i] * mulArg;
    }

    return result;
}
