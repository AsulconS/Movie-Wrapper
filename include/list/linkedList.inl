template <typename T> // Prefix
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
{
    this->current = this->current->rightChild;
    return (*this);
}

template <typename T> // Postfix
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    LinkedList<T>::Iterator it(this->current);
    this->current = this->current->rightChild;
    return it;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator+(uint32 offset) const
{
    LinkedList<T>::Iterator it(*this);
    while(offset--)
    {
        if(it.current != nullptr)
            it.current = it.current->rightChild;
        else break;
    }
    return it;
}

template <typename T>
void LinkedList<T>::print() const
{
    std::cout << "[ ";
    LinkedList<T>::Iterator it;
    for(it = _begin; it != _end; ++it)
        std::cout << (*it)->data << ' ';
    std::cout << ']' << std::endl;
}

template <typename T>
T LinkedList<T>::get(const LinkedList<T>::Iterator& pos) const
{
    return (((*pos)->current) != nullptr) ? *((*pos)->current) : T {} ;
}

template <typename T>
template <typename TArg>
bool LinkedList<T>::search(TArg&& v0)
{
    LinkedList<T>::Iterator it;
    for(it = _begin; it != _end; ++it)
        if((*it)->data == v0)
            return true;

    return false;
}

template <typename T>
template <typename TArg>
void LinkedList<T>::push_front(TArg&& v0)
{
    if(!_size)
    {
        head = new Node<T>(std::forward<TArg>(v0));
        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    Node<T>* node = new Node<T>(std::forward<TArg>(v0));
    node->rightChild = head;
    head = node;
    _begin.current = head;

    ++_size;
}

template <typename T>
template <typename TArg>
void LinkedList<T>::push_back(TArg&& v0)
{
    if(!_size)
    {
        head = new Node<T>(std::forward<TArg>(v0));
        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    Node<T>* node = new Node<T>(std::forward<TArg>(v0));
    last->rightChild = node;
    last = node;

    ++_size;
}

template <typename T>
void LinkedList<T>::pop_front()
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    Node<T>* nodeToDelete = head;
    head = head->rightChild;
    _begin.current = head;

    delete nodeToDelete;
    --_size;
}

template <typename T>
void LinkedList<T>::pop_back()
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    LinkedList<T>::Iterator it = _begin + (_size - 2);
    delete (*it)->rightChild;
    (*it)->rightChild = nullptr;
    last = (*it);

    --_size;
}

template <typename T>
void LinkedList<T>::erase(const LinkedList<T>::Iterator& pos)
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    Node<T>* nodeToDelete = (*pos)->rightChild;
    (*pos)->rightChild = nodeToDelete->rightChild;

    delete nodeToDelete;
    --_size;
}

template <typename T>
void LinkedList<T>::clear()
{
    LinkedList<T>::Iterator it;
    for(it = _begin; it != _end; ++it)
        delete (*it);
    head = nullptr;
    last = nullptr;
    _begin.current = nullptr;
    _size = 0;
}
