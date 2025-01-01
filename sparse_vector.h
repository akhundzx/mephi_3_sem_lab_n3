
//
// Created by akhundzx on 26.12.2024.
//

#ifndef SPARCE_VECTOR_H
#define SPARCE_VECTOR_H
#include "IDictionary.h"
#include "dynamic_array.h"
#include "KeyValue.h"
#include "memory"
#include "stdexcept"
#include <vector>

template <typename TElement>
class SparseVector
{
public:
    SparseVector(int length, UnqPtr<HashTable<int, TElement>> dictionary)
            : length(length), elements(std::move(dictionary)) {}

    ~SparseVector(){}

    int GetLength() const
    {
        return length;
    }

    TElement GetElement(int index) const
    {
        if (index < 0 || index >= length)
        {
            throw std::out_of_range("Index is out of bounds.");
        }

        if (elements->ContainsKey(index))
        {
            return elements->Get(index);
        }
        else
        {
            return TElement();
        }
    }

    void SetElement(int index, const TElement& value)
    {
        if (index < 0 || index >= length)
        {
            throw std::out_of_range("Index is out of bounds.");
        }

        if (value != TElement())
        {
            if (elements->ContainsKey(index))
            {
                elements->Update(index, value);
            }
            else
            {
                elements->Add(index, value);
            }
        }
        else
        {
            RemoveElement(index);
        }
    }

    void RemoveElement(int index) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index is out of bounds.");
        }

        if (elements->ContainsKey(index)) {
            elements->Remove(index);
        }
    }

    void ForEach(void (*func)(int, const TElement&)) const
    {
        auto iterator = elements->GetIterator();
        while (iterator->MoveNext())
        {
            int key = iterator->GetCurrentKey();
            TElement value = iterator->GetCurrentValue();
            func(key, value);
        }
    }

    void Map(TElement (*func)(TElement))
    {
        DynamicArraySmart<KeyValue<int, TElement>> updates;
        auto iterator = elements->GetIterator();
        while (iterator->MoveNext())
        {
            int key = iterator->GetCurrentKey();
            TElement value = iterator->GetCurrentValue();
            TElement newValue = func(value);
            updates.Append(KeyValue<int, TElement>(key, newValue));
        }
        for (int i = 0; i < updates.GetLength(); ++i)
        {
            const KeyValue<int, TElement>& kv = updates.Get(i);
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


    const HashTable<int, TElement>& GetElements() const {
        return *elements;
    }

private:
    int length;
    UnqPtr<HashTable<int, TElement>> elements;
};
#endif //SPARCE_VECTOR_H
