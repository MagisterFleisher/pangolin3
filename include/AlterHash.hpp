#ifndef PANGOLIN_ALTERMAP_HPP
#define PANGOLIN_ALTERMAP_HPP
#pragma GCC optimize("Ofast")
#include <iostream>
#include <map>
#include "Types.hpp"
Altermap GenAllNodeAlter(const Graph& g) {
    std::cout << "\tBegan GenNodeAlter\n";
    Altermap altermap;
    for(const auto& edge : g.edges) {
        altermap.emplace(std::pair(edge.from, edge.to)); 
        altermap.emplace(std::pair(edge.to  , edge.from)); } 
    std::cout << "\tFinished Altermap\n";
    return altermap; }

Altermap GenNodeAlter(const Graph& g, const Node& node) {
    std::cout << "\tBegan GenNodeAlter\n";
    Altermap altermap;
    for(const auto& edge : g.edges) {
        if(node == edge.from) {
            altermap.emplace(std::pair(edge.from, edge.to  ));    }
        if(node == edge.to) {
            altermap.emplace(std::pair(edge.to  , edge.from));    }   } 
    std::cout << "\tFinished Altermap\n"; 
    return altermap; }
#endif // PANGOLIN_ALTERMAP_HPP