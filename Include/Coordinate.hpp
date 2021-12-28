#pragma once

#include <math.h>

namespace sp
{
    class Cord //cordinate
    {
    public:
        inline Cord(int x, int y) : x(x), y(y) {}
        inline Cord() = default;

        inline bool operator==(const Cord &v) const { return (x == v.x) && (y == v.y); }
        inline const Cord operator+(const Cord &v) const { return Cord(x + v.x, y + v.y); }

        static Cord getDelta(const Cord &v1, const Cord &v2) { return Cord(abs(v1.x - v2.x), abs(v1.y - v2.y)); }

        int x;
        int y;
    };

}