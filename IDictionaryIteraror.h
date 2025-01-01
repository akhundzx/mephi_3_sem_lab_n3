//
// Created by akhundzx on 26.12.2024.
//

#ifndef IDICTIONARYITERAROR_H
#define IDICTIONARYITERAROR_H

template <typename TKey, typename TElement>
class IDictionaryIterator
{
public:
    virtual ~IDictionaryIterator() {}

    virtual bool MoveNext() = 0;

    virtual void Reset() = 0;

    virtual TKey GetCurrentKey() const = 0;

    virtual TElement GetCurrentValue() const = 0;
};
#endif //IDICTIONARYITERAROR_H
