#ifndef PANGOLIN_CLIQUEFIND_HPP
#define PANGOLIN_CLIQUEFIND_HPP
#pragma GCC optimize("Ofast")
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include <execution>
#include "Types.hpp"
#include "Degree.hpp"
/*
 * Clique GEN ALGORITHM
 * get alter hash
 * for each node
 *   get node
 *   get alters
 *   for each alter
 *     does node and alter share at least one alter?
 *       A triad is a minimal clique.
 */

// Nodelist MultimapToNodelist
/* 
std::set<std::set<Node>> CliqueFind(const Graph& graph, const Altermap& alter_map) {
    std::set<std::set<Node>>        clique_set;

    std::for_each(std::execution::par, cRANGE(graph.nodes), [&](const auto& node) {
        const auto&                 alter_num       (alter_map.count(node));
        switch(alter_num) {
            case 0: break;
            case 1: break;
            default: {
                auto lower {alter_map.lower_bound(node)};
                auto upper {alter_map.upper_bound(node)};
                Nodelist alters (distance(lower, upper));
                transform(lower, upper, alters.begin(), std::mem_fn(&Altermap::value_type::second));
                // const auto&                 alter_set       (node_alter.second );
                // const auto&                 alter_set_size  (alter_set.size()   );
                // if(alter_set_size > 1) {
                // Altermap::iterator      alter_iterator  (alter_map.find(node));
                // Nodelist                alters;
                std::for_each(std::execution::par, cRANGE(alters), [&](const auto& alter) {
                    
            const std::set<Node>&   alts_alt        (alter_map.at(alter)   );
            const auto&             alts_alt_size   (alts_alt.size());
            if(alts_alt_size > 1) {
            if(alter != node) {
            const auto&             result_size     ((alter_set_size > alts_alt_size) ? alts_alt_size : alter_set_size);
            Nodelist                intersect       (result_size);
            auto                    iterator        (std::set_intersection(cRANGE(alter_set), cRANGE(alts_alt), intersect.begin()));
            intersect.resize(iterator - intersect.begin());
            intersect.shrink_to_fit();
            if(!intersect.empty()) {
                std::set<Node> clique           (cRANGE(intersect));
                clique.emplace(node);
                clique.emplace(alter);
                clique_set.emplace(clique); }}} }); 
    return clique_set; } */
#endif // PANGOLIN_CLIQUEFIND_HPP