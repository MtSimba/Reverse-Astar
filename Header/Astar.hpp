#include <vector>
#include <queue>
#include <functional>
#include "Node.hpp"

namespace sp
{
    using HeuristicFunction = std::function<uint(const Cord &, const Cord &, int)>;

    class Astar
    {
    public:
        Astar();
        std::vector<Cord> findPath(const Cord &startPos, const Cord &targetPos, HeuristicFunction heuristicFunc, int weight = 1);
        void loadMap(const std::string &fileName);
        void setDiagonalMovement(bool enable);

    private:
        std::vector<Cord> buildPath() const;
        bool isValid(const Cord &pos) const;
        bool isBlocked(int index) const;
        int convertTo1D(const Cord &pos) const;

        int m_weight;
        int m_size;
        uint m_nrOfDirections;
        Cord m_dimensions;
        Cord m_startPos;
        Cord m_targetPos;
        std::priority_queue<Node> m_openList;
        std::vector<bool> m_closedList;
        std::vector<Node> m_cameFrom;
        std::vector<int> m_grid;
        std::vector<Cord> m_directions;
        HeuristicFunction m_heuristic;
    };

    namespace heuristic
    {
        uint manhattan(const Cord &v1, const Cord &v2, int weight);
        uint euclidean(const Cord &v1, const Cord &v2, int weight);
    }
}
