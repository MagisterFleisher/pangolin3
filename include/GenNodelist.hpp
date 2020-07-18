#ifndef PANGOLIN_NODELISTGEN_HPP
#define PANGOLIN_NODELISTGEN_HPP
#pragma  GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include "Types.hpp"

Nodelist SquishNodelist(Nodelist& nodes) { //                     std::cout << "\tCalled SquishNodelist\n";
    std::sort(RANGE(nodes));                      // std::execution::par_unseq, 
    auto unique_nodes_iterator = std::unique(RANGE(nodes));
    nodes.erase(unique_nodes_iterator, nodes.end());
    nodes.shrink_to_fit();
    return nodes; }

Nodelist GenNodelist(const Edgelist& edges) {                       std::cout << "Called NodelistGen: Edge count "  << edges.size() << "\n";
    Nodelist nodes;
    for(const auto& edge : edges) { nodes.emplace_back(edge.from); }
    nodes = SquishNodelist(nodes);
    for(const auto& edge : edges) { nodes.emplace_back(edge.to); }
    nodes = std::move(SquishNodelist(nodes));
    return nodes; }
#endif//PANGOLIN_NODELISTGEN_HPP