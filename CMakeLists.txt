cmake_minimum_required(VERSION 3.12)

project(ReverseAstar
             DESCRIPTION "A header only c++ library that implements a reversed version of the A* pathfinder algorithm."
             HOMEPAGE_URL "https://github.com/MtSimba/Reverse-Astar")

add_library(ReverseAstar INTERFACE)

target_include_directories(ReverseAstar INTERFACE .)
