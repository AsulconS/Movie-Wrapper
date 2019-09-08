#ifndef ITERATOR_H
#define ITERATOR_H

#include "core/common.hpp"

template <typename CRTP, typename PtrType = uint8>
class IIterator
{
public:
    explicit IIterator() : current(nullptr) {}
    explicit IIterator(PtrType* _current) : current(_current) {}
    virtual ~IIterator() {}

    IIterator(const IIterator& o) : current(o.current) {}

    virtual CRTP& operator=(const CRTP& o) = 0;

    inline bool operator==(const IIterator& o) const { return this->current == o.current; }
    inline bool operator!=(const IIterator& o) const { return this->current != o.current; }
    inline PtrType* operator*(void) { return this->current; }
    inline const PtrType* operator*(void) const { return this->current; }

    virtual CRTP& operator++() = 0; // Prefix
    virtual CRTP operator++(int) = 0; // Postfix
    virtual CRTP operator+(uint32 offset) const = 0;

    PtrType* current;
};

#endif // ITERATOR_H
