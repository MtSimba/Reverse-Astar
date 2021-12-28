#include <iostream>
#include <string.h>
#include <stdio.h>

#include "Include/Lena.hpp"
#include "Include/Astar.hpp"
#include "Include/Heuristic.hpp"

using namespace sp;

/* display usage */
int help()
{
    std::cout << "Usage: myprogram [-a ] [-l ]" << std::endl;
    std::cout << "\t-a: Astar Algortihm" << std::endl;
    std::cout << "\t-l: Lena Algoritm" << std::endl;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return help();
    }

    for (size_t i = 0; i < (argc); i++)
    {
        if (strcmp("-a", argv[i]) == 0)
        {
            Astar astar;

            std::cout << "############## Astar" << std::endl;

            astar.loadMap("Maps/Map02.txt");
            astar.setDiagonalMovement(true);
            auto path = astar.findPath(Cord(0, 0), Cord(10, 7), heuristic::euclidean, 10);

            for (const auto &coord : path)
            {
                std::cout << coord.x << "," << coord.y << "\n";
            }
        }
        else if (strcmp("-l", argv[i]) == 0)
        {

            Lena lena;
            std::cout << "############## Lena" << std::endl;

            lena.loadMap("Maps/Map02.txt");
            lena.setDiagonalMovement(true);
            auto path = lena.findPath(Cord(0, 0), Cord(10, 7), heuristic::euclidean, 10);

            for (const auto &coord : path)
            {
                std::cout << coord.x << "," << coord.y << "\n";
            }
        }
        else
        {
            std::cout << "Algorithm not Supported. Exiting " << std::endl;
        }
    }
    return 0;
}
