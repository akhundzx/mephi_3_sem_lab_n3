//
// Created by akhundzx on 25.12.2024.
//

#ifndef SPARCEMATRIX_H
#define SPARCEMATRIX_H

#include "IDictionary.h"
#include "IndexPair.h"
#include "unqptr.h"
#include "dynamic_array.h"
#include "KeyValue.h"
#include "HashTable.h"
template<typename TElement>
class SparseMatrix {
private:
    int rows;
    int columns;
    UnqPtr<HashTable<IndexPair, TElement>> elements;
public:
    SparseMatrix(int rows, int columns, UnqPtr<HashTable<IndexPair, TElement>> dictionary)
            : rows(rows), columns(columns), elements(std::move(dictionary)) {}

    ~SparseMatrix() = default;

    int GetRows() const
    {
        return rows;
    }

    int GetColumns() const
    {
        return columns;
    }

    TElement GetElement(int row, int column) const
    {
        if (row < 0 || row >= rows || column < 0 || column >= columns)
        {
            throw std::out_of_range("Row or column index is out of bounds.");
        }

        IndexPair key(row, column);
        if (elements->ContainsKey(key))
        {
            return elements->Get(key);
        }
        else
        {
            return TElement();
        }
    }

    void SetElement(int row, int column, const TElement& value)
    {
        if (row < 0 || row >= rows || column < 0 || column >= columns)
        {
            throw std::out_of_range("Row or column index is out of bounds.");
        }

        IndexPair key(row, column);
        if (value != TElement())
        {
            if (elements->ContainsKey(key))
            {
                elements->Update(key, value);
            }
            else
            {
                elements->Add(key, value);
            }
        }
        else
        {
            RemoveElement(key.row, key.column);
        }
    }

    void RemoveElement(int row, int column) {
        if (row < 0 || row >= rows || column < 0 || column >= columns) {
            throw std::out_of_range("Row or column index is out of bounds.");
        }

        IndexPair key(row, column);
        if (elements->ContainsKey(key)) {
            elements->Remove(key);
        }
    }

    void ForEach(void (*func)(const IndexPair &, const TElement &)) const {
        auto iterator = elements->GetIterator();

        while (iterator->MoveNext()) {
            IndexPair key = iterator->GetCurrentKey();
            TElement value = iterator->GetCurrentValue();
            func(key, value);
        }
    }



    void Map(TElement (*func)(TElement))
    {
        DynamicArraySmart<KeyValue<IndexPair, TElement>> updates;
        auto iterator = elements->GetIterator();
        while (iterator->MoveNext())
        {
            IndexPair key = iterator->GetCurrentKey();
            TElement value = iterator->GetCurrentValue();
            TElement newValue = func(value);
            updates.Append(KeyValue<IndexPair, TElement>(key, newValue));
        }
        for (int i = 0; i < updates.GetLength(); ++i)
        {
            const KeyValue<IndexPair, TElement>& kv = updates.Get(i);
            elements->Update(kv.key, kv.value);
        }
    }


    TElement Reduce(TElement (*func)(TElement, TElement), TElement initial) const
    {
        TElement result = initial;
        auto iterator = elements->GetIterator();
        while (iterator->MoveNext())
        {
            TElement value = iterator->GetCurrentValue();
            result = func(result, value);
        }
        return result;
    }

    UnqPtr<HashTable<IndexPair, TElement>> GetIterator() const
    {
        return elements->GetIterator();
    }

    const HashTable<IndexPair, TElement>& GetElements() const {
        return *elements;
    }


};

#endif //SPARCEMATRIX_H
