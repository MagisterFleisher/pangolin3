#ifndef PANGOLIN_PRESTIGESIMPLE_HPP
#define PANGOLIN_PRESTIGESIMPLE_HPP
#pragma GCC optimize("Ofast")  
#include <algorithm>
#include <execution>
#include <functional>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
#include "Types.hpp"
/* 
* Simple Prestige: the sum of the degree of an actor's alters
* In Prestige: the sum of the degree of in direction alters (actor is .to)
* Out Prestige: the sum of the degree of out direction alters (actor is .from)
* Eigenvalue centrality: also prestige but more complicated
*/
/* 
 * Performance Note:
 * at 1'000'000 edges x 1'000 iterations
 * vector for loop, no execution policies : 1'482'101.986657 ms = 24 minutes 42.101988 seconds
 * for_each, par          unseq           : 1'415'465.532934 ms = 23 minutes 35.465532 seconds 
 * for_each, par_unseq    unseq           : 1'402'769.541336 ms = 23 minutes 22.769544 seconds
 * for_each, par_unseq, unseq, and reduce : 1'370'127.705629 ms = 22 minutes 50.1277056 seconds
*/
/*
 * Simple Prestige
 * for each node,
 *    the node's prestige = sum of it's alters' degree centrality
 */
Attribute PrestigeSimple(Altermap altermap, Attribute degree) { //std::cout << "\tCalled PrestigeSimple\n";
    Attribute                           prestige_map;
    std::for_each(std::execution::par_unseq, RANGE(altermap), [&](const auto& node_alter) {
        const auto&                     node            (node_alter.first );
        const auto&                     alters          (node_alter.second);
        std::vector<std::uint_fast64_t> alter_degree;
        switch(alters.size()) { 
            case 1 : { prestige_map[node] = alters[0]; break; }; 
            default: {
                std::for_each(std::execution::unseq, RANGE(alters), [&](const auto& alter) {
                    alter_degree.emplace_back(degree.at(alter)); });
                prestige_map[node] = std::reduce(std::execution::unseq, cRANGE(alter_degree)); }; }  });
    return prestige_map; }
#endif //PANGOLIN_PRESTIGESIMPLE_HPP