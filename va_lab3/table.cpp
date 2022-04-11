#include "table.h"
#include <fstream>

Table::Table(int size)
    : args(size)
    , vals(size) {}

Table::Table(std::string filename) {
    std::ifstream in(filename);
    int amount;
    in >> amount;
    args.resize(amount);
    vals.resize(amount);

    auto ia = args.begin();
    auto iv = vals.begin();
    for (int i = 0; i < amount; i++) {
        in >> *ia;
        in >> *iv;
    }
}

double &Table::arg(size_t index) { return args[index]; }
double &Table::val(size_t index) { return vals[index]; }
double Table::arg(size_t index) const { return args[index]; }
double Table::val(size_t index) const { return vals[index]; }
size_t Table::size() const { return args.size(); };
