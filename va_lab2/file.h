#pragma once
#include <string>
#include <exception>
#include <fstream>
#include "table.h"

class File {
public:
    static Table loadTable(std::string filename);
    static void saveTable(std::string filename, const Table &table);

private:
    static ArrayDimension readData(std::ifstream &in, const std::vector<std::vector<double>> &args, int level = 0);
    static ArrayDimension readTable(std::ifstream &in, size_t yMax, size_t xMax);
    static void saveData(std::ofstream &out, const ArrayDimension &data);
};
