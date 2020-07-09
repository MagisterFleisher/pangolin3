#ifndef PANGOLIN_ALTERMAP_HPP
#define PANGOLIN_ALTERMAP_HPP
#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>
#include "Types.hpp"
std::set<ID> GenAlters(const ID& node, const Graph& g) {
    std::set<ID>    alters;
    for( const auto& edges : g.edges ) {
        if( node == edges.from )  { alters.emplace(edges.to);   }
        if( node == edges.to   )  { alters.emplace(edges.from); } }
    return alters; }

Alterhash AlterHash(const Graph& g) {
    Alterhash       alter_map;
    std::set<Node>  nodes;
    for(const auto& edge : g.edges ) {
        nodes.emplace(edge.from);
        nodes.emplace(edge.to);}
    for(const auto& node : nodes ) {
        alter_map[node] = GenAlters(node, g); }
    return alter_map; }
#endif // PANGOLIN_ALTERMAP_HPP