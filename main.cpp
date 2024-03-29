#define MW_IMPLEMENTATION
#include "movieWrapper.hpp"

int main()
{
    Downloader::download("https://datasets.imdbws.com/title.basics.tsv.gz");

    //Movie m1(new MovieData {8, "long", "Juanita dos palotes", "Juanita two palotes", 0, 2015, 2020, 6, {"Adventure", "Action"}});
    //Movie m2(new MovieData {16, "short", "Pepito tres palotes", "Pepito three palotes", 1, 2017, 2019, 4, {"Drama", "Action"}});

    OrderedList<Movie> movies {};

    std::size_t count;
    std::cout << "How many movies do you want to load? ";
    std::cin >> count;

    Downloader::load<uint32>(movies, Criteria::BY_ID, true, count);
    std::cout << "OK" << std::endl;

    return 0;
}
