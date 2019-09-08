template <typename T>
UnorderedList<T>::UnorderedList(std::initializer_list<T>&& l) : UnorderedList<T>()
{
    for(const auto& v : l)
        push_back(v);
}

template <typename T>
template <typename TArg>
void UnorderedList<T>::insert(TArg&& v0, const typename UnorderedList<T>::Iterator& pos)
{
    if(!_size)
    {
        head = new Node<T>(std::forward<TArg>(v0));
        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    typename UnorderedList<T>::Iterator it = pos;
    Node<T>* node = new Node<T>(std::forward<TArg>(v0));
    node->rightChild = (*it)->rightChild;
    (*it)->rightChild = node;
    ++_size;
}
