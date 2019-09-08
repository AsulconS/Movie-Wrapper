#ifndef ORDERED_LIST_H
#define ORDERED_LIST_H

#include <algorithm>
#include <vector>

#include "core/common.hpp"
#include "core/iterator.hpp"
#include "core/node.hpp"

#include "list/linkedList.hpp"

template <typename T>
class OrderedList : public LinkedList<T>
{
    using LinkedList<T>::head;
    using LinkedList<T>::last;
    using LinkedList<T>::_size;
    
    using LinkedList<T>::_begin;
    using LinkedList<T>::_end;

    using LinkedList<T>::push_back;
    using LinkedList<T>::push_front;

public:
    explicit OrderedList() : LinkedList<T>() {}
    explicit OrderedList(const T& _head) : LinkedList<T>(_head) {}
    virtual ~OrderedList() { this->clear(); }

    OrderedList(std::initializer_list<T>&& l);

    OrderedList(const OrderedList& o) : LinkedList<T>(o) {}

    template <typename TArg> void insert(TArg&& v0);
};

#endif // ORDERED_LIST_H
