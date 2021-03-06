#pragma once
#include <vector>
#include <queue>
#include <functional>
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>
#include <math.h>

namespace Astar
{

    namespace Cord
    {
        struct Cord //cordinate
        {
            inline Cord(int x, int y) : x(x), y(y) {}
            inline Cord() = default;

            inline bool operator==(const Cord &v) const { return (x == v.x) && (y == v.y); }
            inline const Cord operator+(const Cord &v) const { return Cord(x + v.x, y + v.y); }

            static Cord getDelta(const Cord &v1, const Cord &v2) { return Cord(abs(v1.x - v2.x), abs(v1.y - v2.y)); }

            int x;
            int y;
        };
    }

    namespace Node
    {
        struct Node //node
        {
            Node() : pos(0, 0), parent(-1, -1), f(0), g(0), h(0) {}
            Node(const Cord::Cord &pos, uint f) : pos(pos), parent(-1, 1), f(f), g(0), h(0) {}
            Node(const Cord::Cord &pos, const Cord::Cord &parent, uint f, uint g, uint h) : pos(pos), parent(parent), f(f), g(g), h(h) {}
            Cord::Cord pos;
            Cord::Cord parent;
            uint f;
            uint g;
            uint h;
        };
        inline bool operator<(const Node &a, const Node &b) { return a.f < b.f; }

    }

    namespace heuristic
    {
        uint manhattan(const Cord::Cord &v1, const Cord::Cord &v2, int weight)
        {
            const auto delta = Cord::Cord::getDelta(v1, v2);
            return static_cast<uint>(weight * (delta.x + delta.y));
        }

        uint euclidean(const Cord::Cord &v1, const Cord::Cord &v2, int weight)
        {
            const auto delta = Cord::Cord::getDelta(v1, v2);
            return static_cast<uint>(weight * sqrt((delta.x * delta.x) + (delta.y * delta.y)));
        }

        using HeuristicFunction = std::function<uint(const Cord::Cord &, const Cord::Cord &, int)>;

    }

    class Astar
    {
    public:
        Astar();
        std::vector<Cord::Cord> findPath(const Cord::Cord &startPos, const Cord::Cord &targetPos, heuristic::HeuristicFunction heuristicFunc, int weight = 1);
        void loadMap(const std::string &fileName);
        void setDiagonalMovement(bool enable);

    private:
        std::vector<Cord::Cord> buildPath() const;
        bool isValid(const Cord::Cord &pos) const;
        bool isBlocked(int index) const;
        int convertTo1D(const Cord::Cord &pos) const;

        int m_weight;
        int m_size;
        uint m_nrOfDirections;
        Cord::Cord m_dimensions;
        Cord::Cord m_startPos;
        Cord::Cord m_targetPos;
        std::priority_queue<Node::Node> m_openList;
        std::vector<bool> m_closedList;
        std::vector<Node::Node> m_cameFrom;
        std::vector<int> m_grid;
        std::vector<Cord::Cord> m_directions;
        heuristic::HeuristicFunction m_heuristic;
    };

    Astar::Astar() : m_weight(1),
                     m_dimensions(0, 0),
                     m_startPos(0, 0),
                     m_targetPos(0, 0),
                     m_size(0),
                     m_nrOfDirections(4)
    {
        m_directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    }

    std::vector<Cord::Cord> Astar::findPath(const Cord::Cord &startPos, const Cord::Cord &targetPos, heuristic::HeuristicFunction heuristicFunc, int weight)
    {
        m_startPos = startPos;
        m_targetPos = targetPos;
        m_weight = weight;
        m_heuristic = std::bind(heuristicFunc, m_startPos, m_targetPos, m_weight);
        m_cameFrom.resize(m_size);
        m_closedList.resize(m_size, false);

        m_cameFrom[convertTo1D(m_startPos)].parent = m_startPos;
        m_openList.push(Node::Node(m_startPos, 0));

        uint fNew, gNew, hNew;
        Cord::Cord currentPos;

        while (!m_openList.empty())
        {
            // Get the node with the least f value
            currentPos = m_openList.top().pos;

            if (currentPos == m_targetPos)
            {
                break;
            }

            m_openList.pop();
            m_closedList[convertTo1D(currentPos)] = true;

            // Check the neighbors of the current node
            for (uint i = 0; i < m_nrOfDirections; ++i)
            {
                const auto neighborPos = currentPos + m_directions[i];
                const auto neighborIndex = convertTo1D(neighborPos);

                if (!isValid(neighborPos) || isBlocked(neighborIndex) || m_closedList[neighborIndex] == true)
                {
                    continue;
                }

                gNew = m_cameFrom[convertTo1D(currentPos)].g + 1;
                hNew = m_heuristic(neighborPos, m_targetPos, m_weight);
                fNew = gNew + hNew;

                if (m_cameFrom[neighborIndex].f == 0 || fNew < m_cameFrom[neighborIndex].f)
                {
                    m_openList.push(Node::Node(neighborPos, fNew));
                    m_cameFrom[neighborIndex] = {neighborPos, currentPos, fNew, gNew, hNew};
                }
            }
        }

        return buildPath();
    }

    std::vector<Cord::Cord> Astar::buildPath() const
    {
        std::vector<Cord::Cord> path;
        auto currentPos = m_targetPos;
        auto currentIndex = convertTo1D(currentPos);

        while (!(m_cameFrom[currentIndex].parent == currentPos))
        {
            path.push_back(currentPos);
            currentPos = m_cameFrom[currentIndex].parent;
            currentIndex = convertTo1D(currentPos);
        }

        std::reverse(path.begin(), path.end());

        return path;
    }

    void Astar::loadMap(const std::string &fileName)
    {
        std::ifstream file(fileName);

        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (line.find('w') != std::string::npos)
                {
                    line.erase(std::remove_if(line.begin(), line.end(),
                                              [](unsigned char c)
                                              { return (c == 'w' || c == ':') ? true : false; }),
                               line.end());
                    m_dimensions.x = std::stoi(line);
                }
                else if (line.find('h') != std::string::npos)
                {
                    line.erase(std::remove_if(line.begin(), line.end(),
                                              [](unsigned char c)
                                              { return (c == 'h' || c == ':') ? true : false; }),
                               line.end());
                    m_dimensions.y = std::stoi(line);
                }
                else
                {
                    line.erase(std::remove(line.begin(), line.end(), ','), line.end());

                    for (const auto &c : line)
                    {
                        m_grid.push_back(c - 48);
                    }
                }
            }

            m_size = m_dimensions.x * m_dimensions.y;
            file.close();
        }
    }

    void Astar::setDiagonalMovement(bool enable)
    {
        m_nrOfDirections = (enable) ? 8 : 4;
    }

    bool Astar::isValid(const Cord::Cord &pos) const
    {
        return (pos.x >= 0) && (pos.x < m_dimensions.x) &&
               (pos.y >= 0) && (pos.y < m_dimensions.y);
    }

    bool Astar::isBlocked(int index) const
    {
        return (m_grid[index] == 0);
    }

    // Returns a 1D index based on a 2D coordinate using row-major layout
    int Astar::convertTo1D(const Cord::Cord &pos) const
    {
        return (pos.y * m_dimensions.x) + pos.x;
    }
}
