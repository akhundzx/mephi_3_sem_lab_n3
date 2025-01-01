//
// Created by akhundzx on 25.12.2024.
//

#ifndef ISET_H
#define ISET_H

#include "HashTable.h"

template <typename Tkey>

class ISet {
    private:
    HashTable<Tkey, bool> table;
    public:
    Iset(const int& bucket_counts = 13):table(bucket_counts){}

    void Add(const Tkey& key) {
        table.Add(key, true);
    }

    void Remove(const Tkey& key) {
        table.Remove(key);
    }

    bool Contains(const Tkey& key) {
        return table.ContainsKey(key);
    }
};
#endif //ISET_H
