//
// Created by akhundzx on 26.12.2024.
//

#ifndef TEST_SPARCE_VECTOR_H
#define TEST_SPARCE_VECTOR_H

#include <iostream>
#include "HashTable.h"
#include "sparse_vector.h"

void test_sparse_vector() {
    std::cout << "Testing SparseVector...\n";

    {
        std::cout << "  Using HashTable as storage...\n";
        UnqPtr<HashTable<int, double>> dictionary(new HashTable<int, double>());
        SparseVector<double> vector(5, std::move(dictionary));

        vector.SetElement(0, 1.0);
        vector.SetElement(2, 3.5);
        vector.SetElement(4, -2.2);

        for (int i = 0; i < 5; ++i) {
            std::cout << "    Element[" << i << "] = " << vector.GetElement(i) << "\n";
        }
    }


    std::cout << "SparseVector tests completed.\n";
}

#endif //TEST_SPARCE_VECTOR_H
