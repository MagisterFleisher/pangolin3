#ifndef PANGOLIN_NODELISTGEN_HPP
#define PANGOLIN_NODELISTGEN_HPP
//#pragma  GCC optimize("Ofast")
#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>
#include "Types.hpp"

Nodelist SquishNodelist(Nodelist nodes) {                     std::cout << "\tCalled SquishNodelist\n";
    std::sort(nodes.begin(), nodes.end());                      // std::execution::par_unseq, 
    auto unique_nodes_iterator = std::unique(nodes.begin(), nodes.end());
    nodes.erase(unique_nodes_iterator, nodes.end());
    nodes.shrink_to_fit();
    return nodes; }

Nodelist NodelistGen(Edgelist& edges) {                       std::cout << "Called NodelistGen: Edge count "  << edges.size() << "\n";
    Nodelist nodes;
    for(const auto& edge : edges) { nodes.emplace_back(edge.from); }
    nodes = SquishNodelist(nodes);
    for(const auto& edge : edges) { nodes.emplace_back(edge.to); }
    nodes = SquishNodelist(nodes);
    return nodes; }
#endif//PANGOLIN_NODELISTGEN_HPP