#define MW_IMPLEMENTATION
#include "movieWrapper.hpp"

int main()
{
    UnorderedList<int> l1 {};
    OrderedList<int> l2 {};

    Downloader::download("https://datasets.imdbws.com/title.basics.tsv.gz");

    return 0;
}
