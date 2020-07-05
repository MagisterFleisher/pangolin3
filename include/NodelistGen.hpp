#ifndef PANGOLIN_NODELISTGEN_HPP
#define PANGOLIN_NODELISTGEN_HPP
#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include "Types.hpp"
Nodelist NodelistGen(Edgelist& edges) { std::cout << "Called NodelistGen: Edge count "  << edges.size() << "\n";
    Nodelist nodes;
    for(const auto& edge : edges) {
        nodes.emplace_back(&edge->from); }
    std::cout << "\tRaw from nodelist size: " << nodes.size() << "\nUnsorted: ";

    for(auto node : nodes) {
        std::cout << &node << " "; }
    std::sort(nodes.begin(), nodes.end());
    std::cout << "\n\tSorted: ";
    for(auto node : nodes) {
        std::cout << &node << " "; }
    auto unique_nodes_iterator = std::unique(nodes.begin(), nodes.end());
    nodes.erase(unique_nodes_iterator, nodes.end());
    nodes.shrink_to_fit();
    std::cout << "\tUnique from nodelist size: " << nodes.size() << "\n";
    /* for(const auto& edge : edges)
        std::shared_ptr<ID> id_to (new ID (edge->to));
        nodes.emplace_back(id_to); }
    std::cout << "\tRaw to nodelist size: " << nodes.size() << "\n";
    std::cout << "NodelistGen: Node size: " << nodes.size() << "\n";
    std::sort(nodes.begin(), nodes.end());
    auto unique_nodes_iterator = std::unique(nodes.begin(), nodes.end());
    nodes.resize(std::distance(nodes.begin(), unique_nodes_iterator));
    nodes.shrink_to_fit();
    std::cout << "NodelistGen: Node size: " << nodes.size() << "\n"; */
    return nodes; }
#endif//PANGOLIN_NODELISTGEN_HPP