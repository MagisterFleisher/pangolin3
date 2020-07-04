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

Nodelist NodelistGen(Edgelist edges) {
    Nodelist nodes;
    for(auto& edge : edges) {
        std::shared_ptr<ID> to          (new ID (edge->to));
        nodes.emplace_back(to);
        std::shared_ptr<ID> from        (new ID (edge->from));
        nodes.emplace_back(from);}
    std::cout << nodes.size();
    const auto              unq         = std::unique(nodes.begin(), nodes.end());
    nodes.resize(std::distance(nodes.begin(), unq));
    nodes.shrink_to_fit();
    return nodes; }

/*
std::vector<ID> NodelistGen(std::unique_ptr<Edgelist> edges) { std::cout << "Called NodelistGen" << "\n";
    std::vector<std::unique_ptr<ID>> nodes;
    for(const auto& edge : edges) {
        nodes.emplace_back(edge.from);
        nodes.emplace_back(edge.to); }
    auto last (end(nodes));
    for(auto first (begin(nodes)); first < last; ++first) {
        last = remove(next(first), last, *first); }
    nodes.erase(last, end(nodes));
    return nodes; }
*/
#endif//PANGOLIN_NODELISTGEN_HPP