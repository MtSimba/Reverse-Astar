#pragma once

#include "Coordinate.hpp"

namespace sp
{
    namespace heuristic
    {
        uint manhattan(const Cord &v1, const Cord &v2, int weight)
        {
            const auto delta = Cord::getDelta(v1, v2);
            return static_cast<uint>(weight * (delta.x + delta.y));
        }

        uint euclidean(const Cord &v1, const Cord &v2, int weight)
        {
            const auto delta = Cord::getDelta(v1, v2);
            return static_cast<uint>(weight * sqrt((delta.x * delta.x) + (delta.y * delta.y)));
        }
    }
}
