#include "file.h"

Table File::loadTable(std::string filename) {
    // open file
    std::ifstream in(filename);

    // read dimensions
    int d;
    in >> d;

    // create table
    Table table(d);

    // read dimension args
    for (auto &dv : table.args) {
        int sz;
        in >> sz;
        dv.resize(sz);

        for (auto &v : dv)
            in >> v;
    }


    // read tables (x and y for other = const)
    table.arr = readData(in, table.args);

    in.close();

    return table;
}

ArrayDimension File::readData(std::ifstream &in, const std::vector<std::vector<double>> &args, int level) {
    int dimension = args.size() - level;
    if (dimension == 2) {
        return readTable(in, args[1].size(), args[0].size());
    }
    else {
        ArrayDimension result(dimension);
        result.resize(args[level].size());
        for (size_t i = 0; i < result.size(); i++)
            result[i] = readData(in, args, level + 1);
        return result;
    }
}

ArrayDimension File::readTable(std::ifstream &in, size_t yMax, size_t xMax) {
    ArrayDimension result(2);
    result.resize(yMax);

    for (size_t iy = 0; iy < yMax; iy++) {
        result[iy].resize(xMax);
        for (size_t ix = 0; ix < xMax; ix++) {
            double val;
            in >> val;
            result[iy][ix] = val;
        }
    }

    return result;
}

void File::saveTable(std::string filename, const Table &table) {
    std::ofstream out(filename);

    out << table.arr.getDimension() << '\n';

    for (const auto& argv : table.args) {
        out << argv.size() << ' ';
        for (const auto &arg : argv)
            out << arg << ' ';
        out << '\n';
    }
    out << '\n';

    saveData(out, table.arr);
}

void File::saveData(std::ofstream &out, const ArrayDimension &data) {
    if (data.getDimension() == 2) {
        for (size_t iy = 0; iy < data.size(); iy++) {
            for (size_t ix = 0; ix < data[iy].size(); ix++)
                out << data[iy][ix] << '\t';
            out << '\n';
        }
    }
    else {
        for (size_t i = 0; i < data.size(); i++) {
            saveData(out, data[i]);
            out << '\n';
        }
    }
}
