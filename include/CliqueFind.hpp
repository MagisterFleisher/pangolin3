#ifndef PANGOLIN_TRIADGEN_HPP
#define PANGOLIN_TRIADGEN_HPP
#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include <execution>
#include "Types.hpp"
#include "Degree.hpp"
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
std::set<std::set<Node>> CliqueFind(Alterhash alter_hash) {
    std::set<std::set<Node>>        clique_set;
    std::for_each(std::execution::par, cRANGE(alter_hash), [&](const auto& node_alters){
        const Node                  node            (node_alters.first  );
        const auto&                 alter_set       (node_alters.second );
        const auto&                 alter_set_size  (alter_set.size()   );
        if(alter_set_size > 1) {
            std::for_each(std::execution::par, cRANGE(alter_set), [&](const auto alter){
            const std::set<Node>&   alts_alt        (alter_hash.at(alter)   );
            const auto&             alts_alt_size   (alts_alt.size());
            if(alts_alt_size > 1) {
            if(alter != node) {
            const auto&             result_size     ((alter_set_size > alts_alt_size) ? alts_alt_size : alter_set_size);
            Nodelist                intersect       (result_size);
            auto                    iterator        (std::set_intersection(cRANGE(alter_set), cRANGE(alts_alt), intersect.begin()));
            intersect.resize(iterator - intersect.begin());
            intersect.shrink_to_fit();
            if(!intersect.empty()) {
                std::set<Node>  clique           (cRANGE(intersect));
                clique.emplace(node);
                clique.emplace(alter);
                triad_set.emplace(triad); 
            }}} });} });
    return triad_set; }
#endif // PANGOLIN_TRIADGEN_HPP