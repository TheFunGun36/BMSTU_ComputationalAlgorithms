#include "interpolator.h"
#include <cassert>

Interpolator::Interpolator(const Table &table, const std::vector<size_t> &powers)
    : table(table),
    powers(powers) {
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

    auto range = closestPoints(table.getArgs(level), params[level], powers[level]);

    std::pair<std::vector<double>, std::vector<double>> argData;
    argData.first.resize(range.second - range.first);
    argData.second.resize(range.second - range.first);

    auto it1 = argData.first.begin();
    auto it2 = argData.second.begin();
    for (size_t i = range.first; i < range.second; i++, it1++, it2++) {
        *it1 = table.getArgs(level)[i];
        *it2 = interpolateDimension(tableData[i], params);
    }

    return approxValue(argData, params[level], powers[level]);
}

std::pair<size_t, size_t> closestPoints(std::vector<double> arr, double val, size_t amount) {
    size_t c = 0;
    while (c < arr.size() && arr[c] < val)
        c++;

    size_t amountHalf = amount / 2;
    size_t amountRemainder = amount % 2;
    auto result = std::make_pair(c - amountHalf + 1, c + amountHalf + 1 + amountRemainder);
    // Example:
    //     0   1  [2]  3   4   5   6
    //         4     ^         4
    //         5                   5

    if (result.first < 0) {
        result.second -= result.first;
        result.first = 0;
        assert(result.second < arr.size());
    }
    else if (result.second > arr.size()) {
        size_t shift = result.second - arr.size() + 1;
        result.first -= shift;
        result.second -= shift;
        assert(result.first >= 0);
    }

    return result;
}

double Interpolator::approxValue(
        const std::pair<std::vector<double>, std::vector<double>> &data,
        double param,
        size_t power) {
    const std::vector<double> &args(data.first);
    std::vector<double> buff1(data.second);
    std::vector<double> buff2(buff1.size() - 1);
    std::vector<double> &val1 = buff1;
    std::vector<double> &val2 = buff2;

    for (int i = 0; i < buff1.size() - 1; i++) {
        for (int j = 0; j < buff1.size() - i - 1; j++) {
            double arg1 = args[j];
            double arg2 = args[j + i + 1];
        }
    }
}
