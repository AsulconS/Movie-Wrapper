#include <iostream>

#define LIST_IMPLEMENTATION
#include "list/list.hpp"

int main()
{
    UnorderedList<int> list {1, 2, 3, 4, 5};
    list.print();

    list.pop_front();
    list.print();

    list.pop_back();
    list.print();

    list.insert(7, list.begin() + 1);
    list.print(); // https://datasets.imdbws.com/title.basics.tsv.gz

    return 0;
}
