//
// Created by akhundzx on 25.12.2024.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "dynamic_array.h"
#include "IDictionary.h"
#include "linked_list.h"
#include "IDictionaryIteraror.h"
#include <iostream>
#include <functional>
#include <stdexcept>
#include <type_traits>

template <typename Tkey, typename TElement>
class HashTable{
private:
    struct Pair{
        Tkey key;
        TElement element;
        Pair(const Tkey& k,const TElement& elem): key(k),element(elem){}
    };

    UnqPtr<DynamicArraySmart<LinkedListSmart<Pair>>> table;
    int count;
    int capacity;

    size_t HashFunction(const Tkey& key) const{
        if constexpr (std::is_same<Tkey, IndexPair>::value) {
            return IndexPairHash()(key);
        } else {
            return std::hash<Tkey>()(key);
        }
    }

    void rehash(){
        int new_capacity = capacity*2;
        UnqPtr<DynamicArraySmart<LinkedListSmart<Pair>>> new_table(new DynamicArraySmart<LinkedListSmart<Pair>>(new_capacity));
        for (int i = 0; i < new_capacity;i++){
            new_table->Append(LinkedListSmart<Pair>());
        }
        for (int i = 0; i < capacity;i++){
            LinkedListSmart<Pair>& chain = table->Get(i);
            for (int j = 0; j < chain.GetLength();++j){
                Pair &p = chain.Get(j);
                int index = HashFunction(p.key)%capacity;
                new_table->Get(index).Append(p);
            }
        }
    }
public:
    explicit HashTable(const int c = 13): table(new DynamicArraySmart<LinkedListSmart<Pair>>(c)),count(0),capacity(c)
    {
        for (int i = 0; i < capacity;i++)
            table->Append(LinkedListSmart<Pair>());
    }

    int GetCount() const {
        return count;
    }

    int GetCapacity() const {
        return capacity;
    }

    TElement Get(const Tkey& key) const {
        int index = HashFunction(key)%capacity;
        const LinkedListSmart<Pair> &chain = table->Get(index);
        for (int i = 0; i < chain.GetLength();i++){
            if (chain.Get(i).key == key){
                return chain.Get(i).element;
            }
        }
        throw std::runtime_error("Key not in Table");
    }

    bool ContainsKey(const Tkey& key) const {
        int index = HashFunction(key)%capacity;
        const LinkedListSmart<Pair> &chain = table->Get(index);
        for (int i = 0; i < chain.GetLength();i++){
            if (chain.Get(i).key == key){
                return true;
            }
        }
        return false;
    }

    void Add(const Tkey& key,const TElement& elem){
        int index = HashFunction(key)%capacity;
        LinkedListSmart<Pair> &chain = table->Get(index);
        for (int i = 0; i < chain.GetLength();i++){
            if (chain.Get(i).key == key){
                chain.Get(i).element = elem;
                return;
            }
        }
        chain.Append(Pair(key,elem));
        count++;

        if(count + 1 == capacity){
            rehash();
        }
    }

    void Update(const Tkey &key, const TElement &element) {
        size_t index = HashFunction(key) % capacity;
        LinkedListSmart<Pair> &chain = table->Get(static_cast<int>(index));

        for (int i = 0; i < chain.GetLength(); ++i) {
            if (chain.Get(i).key == key) {
                chain.Get(i).element = element;
                return;
            }
        }

        throw std::runtime_error("Key not found.");
    }
    void Remove(const Tkey& key) {
        int index = HashFunction(key)%capacity;
        LinkedListSmart<Pair>& chain = table->Get(index);
        for (int i = 0; i < chain.GetLength();i++){
            if (chain.Get(i).key == key){
                chain.RemoveAt(i);
                --count;
                return;
            }
        }
        throw std::runtime_error("Key not in table.");
    }


    ~HashTable() = default;

    class HashTableIterator {
    public:
        HashTableIterator(const HashTable *hashTable): hashTable(hashTable), bucketIndex(0), listIndex(-1) {}

        ~HashTableIterator() = default;

        bool MoveNext()  {
            ++listIndex;
            while (bucketIndex < hashTable->capacity) {
                LinkedListSmart<Pair> &chain = hashTable->table->Get(static_cast<int>(bucketIndex));
                if (listIndex < chain.GetLength()) {
                    return true;
                } else {
                    ++bucketIndex;
                    listIndex = 0;
                }
            }
            return false;
        }

        void Reset() {
            bucketIndex = 0;
            listIndex = -1;
        }

        Tkey GetCurrentKey() const {
            if (bucketIndex >= hashTable->capacity)
                throw std::out_of_range("Iterator out of range");

            const LinkedListSmart<Pair> &chain = hashTable->table->Get(static_cast<int>(bucketIndex));
            return chain.Get(listIndex).key;
        }

        TElement GetCurrentValue() const {
            if (bucketIndex >= hashTable->capacity)
                throw std::out_of_range("Iterator out of range");

            const LinkedListSmart<Pair> &chain = hashTable->table->Get(static_cast<int>(bucketIndex));
            return chain.Get(listIndex).element;
        }


    private:
        const HashTable *hashTable;
        size_t bucketIndex;
        int listIndex;
    };

    UnqPtr<HashTableIterator> GetIterator() const {
        return UnqPtr<HashTableIterator>(new HashTableIterator(this));
    }

};
#endif //HASHTABLE_H
