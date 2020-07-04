#ifndef PANGOLIN_NODELISTGEN_HPP
#define PANGOLIN_NODELISTGEN_HPP
#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>
#include "Types.hpp"

std::vector<ID> NodelistGen(const Edgelist& edges) { std::cout << "Called NodelistGen" << "\n";
    std::vector<ID> nodes;
    for(const auto& edge : edges) {
        nodes.emplace_back(edge.from);
        nodes.emplace_back(edge.to); }
    auto last (end(nodes));
    for(auto first (begin(nodes)); first < last; ++first) {
        last = remove(next(first), last, *first); }
    nodes.erase(last, end(nodes));
    return nodes; }

#endif//PANGOLIN_NODELISTGEN_HPP