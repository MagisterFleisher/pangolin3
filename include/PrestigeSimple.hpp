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
 /* 
Attribute PrestigeSimple(Altermap alters_map, Attribute degree) {
    std::cout << "\tCalled PrestigeSimple\n";
    Attribute                   prestige_map    {};
    for(const auto& alter_map : alters_map) {
        const auto&             node            (alter_map.first );
        const auto&             alter           (alter_map.second);
        const auto&             alter_degree    (degree.at(alter));
        prestige_map[node] += alter_degree; }
    return prestige_map; } */
#endif //PANGOLIN_PRESTIGESIMPLE_HPP