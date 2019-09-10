#ifndef NODE_H
#define NODE_H

#include <memory>

#include "core/common.hpp"

template <typename T>
class Node
{
public:
    Node(const T& _data) : data(_data), leftChild(nullptr), rightChild(nullptr) {}
    Node(T&& _data) : data(std::move(_data)), leftChild(nullptr), rightChild(nullptr) {}

    T data;
    Node<T>* leftChild;
    Node<T>* rightChild;
};

#endif // NODE_H
