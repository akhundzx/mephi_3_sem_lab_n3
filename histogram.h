//
// Created by akhundzx on 26.12.2024.
//

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "HashTable.h"
#include <iostream>

template <typename T>
class Histogram {
private:
    HashTable<T, int> table;
public:
    explicit Histogram(int capacity = 13) : table(capacity) {}
    void Add(const T& value) {
        if (table.ContainsKey(value)) {
            int count = table.Get(value);
            table.Update(value, count + 1);
        } else {
            table.Add(value, 1);
        }
    }
    void Remove(const T& value) {
        if (table.ContainsKey(value)) {
            int count = table.Get(value);
            if (count > 1) {
                table.Update(value, count - 1);
            } else {
                table.Remove(value);
            }
        } else {
            throw std::runtime_error("Element not found in histogram.");
        }
    }


    int GetCount(const T& value) const {
        if (table.ContainsKey(value)) {
            return table.Get(value);
        }
        return 0;
    }


    void Print() const {
        auto iterator = table.GetIterator();
        while (iterator->MoveNext()) {
            std::cout << iterator->GetCurrentKey() << ": " << iterator->GetCurrentValue() << std::endl;
        }
    }


    int TotalCount() const {
        return table.GetCount();
    }
};
#endif //HISTOGRAM_H
