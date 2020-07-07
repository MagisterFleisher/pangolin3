#ifndef PANGOLIN_SIMPLEPRESTIGE_HPP
#define PANGOLIN_SIMPLEPRESTIGE_HPP
#pragma GCC optimize("Ofast")  
#include <algorithm>
#include <future>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Types.hpp"
/* 
Simple Prestige: the sum of the degree of an actor's alters
In Prestige: the sum of the degree of in direction alters (actor is .to)
Out Prestige: the sum of the degree of out direction alters (actor is .from)
Eigenvalue centrality: also prestige but more complicated
*/
/*
 * Simple Prestige
 * for each node,
 *    the node's prestige = sum of it's alters' degree centrality
 */
Alterhash PrestigeSimple(Alterhash alterhash, Nodelist nodelist, std::unordered_map degree) {
    std::unordered_map<Node, std::uint64_t>  prestige_map;
    std::for_each(const auto& node : Nodelist) {
        const auto&                     alters      (alterhash[node]);
        freq_map[node] = std::accumulate(alters.begin(), alters.end(), 0); }
    return freq_map; }
#endif //PANGOLIN_SIMPLEPRESTIGE_HPP