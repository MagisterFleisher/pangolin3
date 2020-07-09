#ifndef PANGOLIN_PRESTIGESIMPLE_HPP
#define PANGOLIN_PRESTIGESIMPLE_HPP
#pragma GCC optimize("Ofast")  
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <execution>
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
std::unordered_map<Node, std::uint64_t> PrestigeSimple(Altermap alter_hash, std::unordered_map<Node, std::uint64_t> degree) {
    std::cout << "\tCalled PrestigeSimple\n";
    Attribute                  prestige_map    {};
    /* std::for_each(cRANGE(alter_hash), [&](const auto& node_map){
        const auto&             node            (node_map.first);
        const auto&             alters          (node_map.second);
        std::uint64_t           prestige        (0);
        for(const auto& alter : alters) {
            const auto&         alter_degree    (degree.at(alter));
            prestige += alter_degree; }
        prestige_map[node] = prestige; }); */
    return prestige_map; }
#endif //PANGOLIN_PRESTIGESIMPLE_HPP