#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <string>

class Table {
public:
    Table(int size);
    Table(std::string filename);
    double &arg(size_t index);
    double &val(size_t index);
    double arg(size_t index) const;
    double val(size_t index) const;
    size_t size() const;

private:
    std::vector<double> args;
    std::vector<double> vals;
};

#endif // TABLE_H
