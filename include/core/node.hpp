#ifndef NODE_H
#define NODE_H

#include "core/common.hpp"

template <typename T>
class Node
{
public:
    Node(const T& _data) : data(_data), leftChild(nullptr), rightChild(nullptr) {}

    const T data;
    Node<T>* leftChild;
    Node<T>* rightChild;
};

#endif // NODE_H
