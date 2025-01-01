//
// Created by akhundzx on 25.12.2024.
//

#ifndef INDEXPAIR_H
#define INDEXPAIR_H

#include <iostream>

struct IndexPair {
    int row;
    int column;
    IndexPair(int r, int c) {
        row = r;
        column = c;
    }
    IndexPair():row(0),column(0){}

    bool operator==(const IndexPair& other) const {
        return row == other.row && column == other.column;
    }

    bool operator<(const IndexPair& other) const {
        if (row != other.row)
            return row < other.row;
        return column < other.column;
    }

    bool operator>(const IndexPair& other) const {
        if (row != other.row)
            return row > other.row;
        return column > other.column;
    }
};

inline std::ostream& operator<<(std::ostream& os, const IndexPair& ip) {
    os << "(" << ip.row << ", " << ip.column << ")";
    return os;
}

struct IndexPairHash {
    size_t operator()(const IndexPair& k) const {
        size_t row_hash = static_cast<size_t>(k.row) * 73856093;
        size_t col_hash = static_cast<size_t>(k.column) * 19349663;
        return row_hash ^ (col_hash * 2654435761);
    }
};

#endif //INDEXPAIR_H
