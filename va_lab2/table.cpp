#include "table.h"
#include <cassert>

Table::Table(int dimension) {
    assert(dimension > 2);
}

size_t Table::dimension() const {
    return args.size();
}
