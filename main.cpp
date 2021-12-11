#include <iostream>

#include "Header/Lena.hpp"
#include "Header/Astar.hpp"

using namespace sp;

int main()
{
    Astar astar;

    std::cout << "############## Astar" << std::endl;

    astar.loadMap("Maps/Map02.txt");
    astar.setDiagonalMovement(true);
    auto path2 = astar.findPath(Cord(0, 0), Cord(10, 7), heuristic::euclidean, 10);

    for (const auto &coord : path2)
    {
        std::cout << coord.x << "," << coord.y << "\n";
    }

    /*Lena lena;
    std::cout << "############## Lena" << std::endl;


    lena.loadMap("Maps/Map02.txt");
    lena.setDiagonalMovement(true); 
    auto path1 = lena.findPath(Cord(0, 0), Cord(10, 7), heuristic::euclidean, 10);

    for (const auto &coord : path1)
    {
        std::cout << coord.x << "," << coord.y << "\n";
    }*/


    return 0;
}