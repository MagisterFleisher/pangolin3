#ifndef PANGOLIN_ALTERMAP_HPP
#define PANGOLIN_ALTERMAP_HPP
#pragma GCC optimize("Ofast")
#include <execution>
#include <iostream>
#include <map>
#include "Types.hpp"
#include "GenNodelist.hpp"

Altermap GenAllAlters(const Graph& g) {
    std::cout << "\tBegan GenAllAlters\n";
    Altermap        altermap;
    std::for_each(std::execution::seq, RANGE(g.nodes), [&altermap, g](const auto& node) {
        Nodelist    alters;
        std::for_each(std::execution::seq, RANGE(g.edges), [&alters, node](const auto& edge) {
            if(node == edge.from) {         alters.emplace_back(edge.to); 
            } else if(node == edge.to) {    alters.emplace_back(edge.from); } });
        altermap[node] = SquishNodelist(alters); });
    std::cout << "\tFinished Altermap\n";
    return altermap; }

Altermap GenAlters(const Graph& g, const Node& node) {
    std::cout << "\tBegan GenAlters\n";
    Altermap altermap;
    for(const auto& edge : g.edges) {
        if(node == edge.from) {
            altermap.emplace(std::pair(edge.from, edge.to  ));}
        if(node == edge.to) {
            altermap.emplace(std::pair(edge.to  , edge.from));}} 
    std::cout << "\tFinished Altermap\n"; 
    return altermap; }
#endif // PANGOLIN_ALTERMAP_HPP