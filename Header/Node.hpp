#ifndef NODE_HPP
#define NODE_HPP
#pragma once 

#include "Coordinate.hpp"

namespace sp
{

    struct Node
    {
        Node() : pos(0, 0), parent(-1, -1), f(0), g(0), h(0) {}
        Node(const Cord &pos, uint f) : pos(pos), parent(-1, 1), f(f), g(0), h(0) {}
        Node(const Cord &pos, const Cord &parent, uint f, uint g, uint h) : pos(pos), parent(parent), f(f), g(g), h(h) {}
        Cord pos;
        Cord parent;
        uint f;
        uint g;
        uint h;
    };

    inline bool operator<(const Node &a, const Node &b) { return a.f < b.f; }

}

#endif