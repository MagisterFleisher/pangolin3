/*
 * TRIAD GEN ALGORITHM
 * get alter hash
 * for each node
 *   get node
 *   get alters
 *   for each alter
 *     does node and alter share an alter?
 *       create triads for each alter (node, alter, shared alter) 
 */
#ifndef NET1_ALTERMAP_HPP
#define NET1_ALTERMAP_HPP
#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>
#include "Types.hpp"
Alterhash TriadGen(Alterhash alter_hash) {
    Alterhash triad_map;
    std::for_each(cRANGE(alter_hash), [alter_hash, &triad_map](const auto& node_alters){
        const Node          node                (node_alters.first);
        const std::set      alter_set           (node_alters.second);
        std::for_each(cRANGE(alter_set), [node, alter_set, alter_hash, &triad_map](const auto alter){
            const Node&     immediate_alter     (alter.first        );
            const std::set  alters_set_of_alter (alter_hash.at(node)   );
            Nodelist        intersect;
            auto            iterator            (std::set_intersection (cRANGE(alter_set), cRANGE(alters_set_of_alter), intersect.begin()));
            intersect.resize(iterator - intersect.begin());
            intersect.shrink_to_fit();
            if(intersect.empty() == false) { 
                std::sort(RANGE(intersect));
                for(const auto& triad_node : intersect) {
                    const std::set<Node> triad  ({ node, immediate_alter, triad_node});
                    triad_map.emplace(triad); } } } ); });
    return triad_map; }
#endif // NET1_ALTERMAP_HPP