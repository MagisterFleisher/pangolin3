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
    std::cout << "\tBeginning gen loop 1\n";

    std::for_each(std::execution::unseq, cRANGE(g.edges), [&altermap](const auto& edge) {
        Nodelist raw_from (altermap[edge.from]);
        raw_from.emplace_back(edge.to);
        altermap[edge.from] = std::move(raw_from); });
    
    std::cout << "\tBeginning Squish loop 1\n";
    std::for_each(std::execution::par_unseq, cRANGE(altermap), [&altermap](auto node_alter) {
        altermap[node_alter.first] = std::move(SquishNodelist(node_alter.second)); });

    std::cout << "\tBeginning gen loop 2\n";
    std::for_each(std::execution::unseq, cRANGE(g.edges), [&altermap](const auto& edge) {
        Nodelist raw_to (altermap[edge.to]);
        raw_to.emplace_back(edge.from);
        altermap[edge.to] = std::move(raw_to); });

    std::cout << "\tBeginning Squish loop2\n";
    std::for_each(std::execution::par_unseq, cRANGE(altermap), [&altermap](auto node_alter) {
        altermap[node_alter.first] = std::move(SquishNodelist(node_alter.second)); });
    
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