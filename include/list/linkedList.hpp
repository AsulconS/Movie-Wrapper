#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "core/common.hpp"
#include "core/iterator.hpp"
#include "core/node.hpp"

template <typename T>
class LinkedList
{
public:
    class Iterator : public IIterator<LinkedList<T>::Iterator, Node<T>>
    {
    public:
        explicit Iterator() : IIterator<LinkedList<T>::Iterator, Node<T>>() {}
        explicit Iterator(Node<T>* _current) : IIterator<LinkedList<T>::Iterator, Node<T>>(_current) {}
        virtual ~Iterator() {}

        virtual Iterator& operator=(const Iterator& o) override { this->current = o.current; return (*this); }

        virtual Iterator& operator++() override; // Prefix
        virtual Iterator operator++(int) override; // Postfix
        virtual Iterator operator+(uint32 offset) const override;
    };

public:
    explicit LinkedList() : head(nullptr), last(nullptr), _size(0), _begin(LinkedList<T>::Iterator(nullptr)), _end(LinkedList<T>::Iterator(nullptr)) {}
    explicit LinkedList(const T& _head) : head(new Node<T>(_head)), last(head), _size(1), _begin(LinkedList<T>::Iterator(head)), _end(LinkedList<T>::Iterator(nullptr)) {}
    virtual ~LinkedList() { clear(); }

    LinkedList(const LinkedList& o) : head(o.head), last(o.last), _size(o._size), _begin(o._begin), _end(o._end) {}

    inline const LinkedList<T>::Iterator& begin() & { return this->_begin; }
    inline const LinkedList<T>::Iterator& end() & { return this->_end; }

    void print() const;
    inline size_t size() const { return this->_size; }
    inline bool empty() const { return !this->_size; }

    T get(const LinkedList<T>::Iterator& pos) const;
    inline T front() { return *head; }
    inline T back() { return *last; }
    template <typename TArg> bool search(TArg&& v0);

    template <typename TArg> void push_front(TArg&& v0);
    template <typename TArg> void push_back(TArg&& v0);

    void pop_front();
    void pop_back();
    void erase(const LinkedList<T>::Iterator& pos);
    void clear();
    
protected:
    Node<T>* head;
    Node<T>* last;
    size_t _size;

    LinkedList<T>::Iterator _begin;
    LinkedList<T>::Iterator _end;
};

#endif // LINKED_LIST_H
