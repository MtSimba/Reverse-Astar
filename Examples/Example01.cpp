#include <iostream>
#include <string>

#include "../Include/Lena.hpp"
#include "../Include/Astar.hpp"


/* display usage */
int help()
{
    std::cout << "Usage: program [-h] [--help] [-a ] [-l ] : [map]" << std::endl;
    std::cout << "\t-h | --help: program usage" << std::endl;
    std::cout << "\t-a: Astar Algortihm" << std::endl;
    std::cout << "\t-l: Lena Algoritm" << std::endl;
    std::cout << "\tmap : map to search through. Test maps located in Maps/Mapxx.txt" << std::endl;
    return 1;
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return help();
    }
    for (size_t i = 0; i < argc; i++)
    {
        std::cout << "argument " << i << " : " << argv[i] << std::endl;
    }

    using namespace std::literals;
    if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
    {
        return help();
    }

    else if (std::string(argv[1]) == "-a")
    {
        Astar::Astar astar;

        std::cout << "############## Astar" << std::endl;

        if (argc < 3)
            astar.loadMap("Maps/Map01.txt");
        else
            astar.loadMap(argv[2]);

        astar.setDiagonalMovement(false);
        auto path = astar.findPath(Astar::Cord::Cord(0, 0), Astar::Cord::Cord(10, 7), Astar::heuristic::euclidean, 10);

        for (const auto &coord : path)
        {
            std::cout << coord.x << "," << coord.y << "\n";
        }
        std::cout << "total fields crossed : " << path.size() << std::endl;
    }
    else if (std::string(argv[1]) == "-l")
    {

        Lena::Lena lena;
        std::cout << "############## Lena" << std::endl;

        if (argc < 3)
            lena.loadMap("Maps/Map01.txt");
        else
            lena.loadMap(argv[2]);

        lena.setDiagonalMovement(false);
        auto path = lena.findPath(Lena::Cord::Cord(0, 0), Lena::Cord::Cord(10, 7), Lena::heuristic::euclidean, 10);

        for (const auto &coord : path)
        {
            std::cout << coord.x << "," << coord.y << "\n";
        }
        std::cout << "total fields crossed : " << path.size() << std::endl;
    }

    return 0;
}
