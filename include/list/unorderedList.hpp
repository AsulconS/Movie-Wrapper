#ifndef UNORDERED_LIST_H
#define UNORDERED_LIST_H

#include "core/common.hpp"
#include "core/iterator.hpp"
#include "core/node.hpp"

#include "list/linkedList.hpp"

template <typename T>
class UnorderedList : public LinkedList<T>
{
    using LinkedList<T>::head;
    using LinkedList<T>::last;
    using LinkedList<T>::_size;
    
    using LinkedList<T>::_begin;
    using LinkedList<T>::_end;

    using LinkedList<T>::push_back;

public:
    explicit UnorderedList() : LinkedList<T>() {}
    explicit UnorderedList(const T& _head) : LinkedList<T>(_head) {}
    virtual ~UnorderedList() { this->clear(); }

    UnorderedList(std::initializer_list<T>&& l);

    UnorderedList(const UnorderedList& o) : LinkedList<T>(o) {}

    template <typename TArg> void insert(TArg&& v0, const typename UnorderedList<T>::Iterator& pos);
};

#endif // UNORDERED_LIST_H
