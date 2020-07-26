#ifndef PANGOLIN_DEGREECENTRALITY_HPP
#define PANGOLIN_DEGREECENTRALITY_HPP
#pragma GCC optimize("Ofast")  
#include <algorithm>
#include <execution>
#include <iostream>
#include <unordered_map>
#include "Types.hpp"
/*
// Can use Futures
Attribute DegreeTo(const Edgelist& edges, Attribute freq_map) {
    std::for_each(std::execution::unseq, cRANGE(edges), [&freq_map](const auto& edge){ freq_map[edge.to] += 1; });
    return freq_map; }
Attribute DegreeFrom(const Edgelist& edges, Attribute freq_map) {
    std::for_each(std::execution::unseq, cRANGE(edges), [&freq_map](const auto& edge){ freq_map[edge.to] += 1; });
    return freq_map; } */
/*
 * @NAME: Degree
 * @PURPOSE: Count occurences of elements in a vector.  Return a map.
 */
Attribute Degree(const Graph& g, Direction direction) {
    Attribute freq_map {};
    std::for_each(std::execution::unseq, cRANGE(g.nodes), [&freq_map](const auto& node){ freq_map[node] += 0; });
    switch(direction) {
        case in:    {
            std::for_each(std::execution::unseq, cRANGE(g.edges), [&freq_map](const auto& edge){ freq_map[edge.to] += 1; });
            return freq_map; };
        case out:   {
            std::for_each(std::execution::unseq, cRANGE(g.edges), [&freq_map](const auto& edge){ freq_map[edge.from] += 1; });
            return freq_map; };
        case both:  {
            std::for_each(std::execution::unseq, cRANGE(g.edges), [&freq_map](const auto& edge){ freq_map[edge.to] += 1;   });
            std::for_each(std::execution::unseq, cRANGE(g.edges), [&freq_map](const auto& edge){ freq_map[edge.from] += 1; });
            return freq_map; };
        default:    {
            std::cerr << "Degree: Error, no valid direction for switch";
            return freq_map; }; }
    return freq_map; }
#endif //PANGOLIN_DEGREECENTRALITY_HPP