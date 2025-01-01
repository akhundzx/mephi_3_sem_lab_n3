//
// Created by akhundzx on 26.12.2024.
//

#ifndef TEST_SPARCE_MATRIX_H
#define TEST_SPARCE_MATRIX_H
#include <iostream>
#include "sparcematrix.h"
#include "HashTable.h"

void test_sparse_matrix() {
    std::cout << "Testing SparseMatrix...\n";

    {
        std::cout << "  Using HashTable as storage...\n";
        UnqPtr<HashTable<IndexPair, double>> dictionary(new HashTable<IndexPair, double>());
        SparseMatrix<double> matrix(5, 5, std::move(dictionary));

        matrix.SetElement(0, 0, 1.0);
        matrix.SetElement(1, 1, 2.0);
        matrix.SetElement(2, 2, 3.0);
        matrix.SetElement(4, 2, 5.0);
        for (int i = 0; i < 5; ++i) {
            std::cout << "    ";
            for (int j = 0; j < 5; ++j) {
                std::cout << "[" << matrix.GetElement(i, j) << "]";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "SparseMatrix tests completed.\n";
}


#endif //TEST_SPARCE_MATRIX_H
