#define MW_IMPLEMENTATION
#include "movieWrapper.hpp"

int main()
{
    Downloader::download("https://datasets.imdbws.com/title.basics.tsv.gz");

    Movie m1(new MovieData {16, "short", "Pepito tres palotes", "Pepito three palotes", 1, 2017, 2019, 4, {"Drama", "Action"}});
    Movie m2(new MovieData {8, "long", "Juanita dos palotes", "Juanita two palotes", 0, 2015, 2020, 6, {"Adventure", "Action"}});

    m1.setCriteria<uint32>(Criteria::BY_ID);
    m2.setCriteria<uint32>(Criteria::BY_ID);

    OrderedList<Movie> l {};
    l.insert(m1);
    l.insert(m2);

    std::cout << (m1 >= m2) << std::endl;
    l.print();

    return 0;
}
