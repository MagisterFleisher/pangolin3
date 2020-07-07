#ifndef PANGOLIN_DEGREECENTRALITY_HPP
#define PANGOLIN_DEGREECENTRALITY_HPP
#pragma GCC optimize("Ofast")  
#include <algorithm>
#include <future>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Types.hpp"
#define RANGE(x)  x.begin(),  x.end()
#define cRANGE(x) x.cbegin(), x.cend()
/*
 * @NAME: Freq
 * @PURPOSE: Count occurences of elements in a vector.  Return a map.
 */
std::unordered_map<ID, std::uint64_t> Freq(const Nodelist& to_count) {
    std::unordered_map<ID, std::uint64_t> freq_map;
    for(const auto& element : to_count) { freq_map[element] += 1; }
    return freq_map; }
/*
 * @NAME: OutNodes
 * @PURPOSE: Return a vector of nodes used in edges
 */
Nodelist OutNodes(const Edgelist& edges) {
    Nodelist nodes;
    for(const auto& edge : edges) { nodes.emplace_back(edge.from);  }
    return nodes; }
/*
 * @NAME: InNodes
 * @PURPOSE: Return a vector of nodes used in edges
 */
Nodelist InNodes(const Edgelist& edges) {
    Nodelist nodes;
    for(const auto& edge : edges) { nodes.emplace_back(edge.to);  }
    return nodes; }
/*
 * @NAME: AllNodes
 * @PURPOSE: Return a vector of nodes used in all edges
 */
std::vector<ID> AllNodes(const Edgelist& edges) {
    auto            vectorA       (OutNodes(edges));
    const auto&     vectorB       (InNodes( edges));
    vectorA.insert(vectorA.end(), cRANGE(   vectorB));
    return vectorA; }

std::unordered_map<ID, std::uint64_t> SimpleDegree( const Graph& g) { return Freq(AllNodes(g.edges)); }
std::unordered_map<ID, std::uint64_t> OutDegree(    const Graph& g) { return Freq(OutNodes(g.edges)); }
std::unordered_map<ID, std::uint64_t> InDegree(     const Graph& g) { return Freq(InNodes( g.edges)); }
#endif //PANGOLIN_DEGREECENTRALITY_HPP