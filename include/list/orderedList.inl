template <typename T>
OrderedList<T>::OrderedList(std::initializer_list<T>&& l) : LinkedList<T>()
{
    std::vector<T> temp;
    for(const auto& v : l)
        temp.push_back(v);
    
    std::sort(temp.begin(), temp.end());
    for(const auto& v : temp)
        push_back(v);
}

template <typename T>
template <typename TArg>
void OrderedList<T>::insert(TArg&& v0)
{
    if(!_size)
    {
        head = new Node<T>(std::forward<TArg>(v0));
        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    if(head->data >= v0)
    {
        push_front(std::forward<TArg>(v0));
        return;
    }
    if(last->data <= v0)
    {
        push_back(std::forward<TArg>(v0));
        return;
    }

    Node<T>* node = new Node<T>(std::forward<TArg>(v0));
    typename OrderedList<T>::Iterator it = _begin;
    while((*it)->rightChild != nullptr)
    {
        if((node->data >= (*it)->data) && (node->data <= (((*it)->rightChild))->data))
        {
            node->rightChild = (*it)->rightChild;
            (*it)->rightChild = node;
            ++_size;
            return;
        }
        ++it;
    }
}
