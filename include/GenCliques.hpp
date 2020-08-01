#ifndef PANGOLIN_GENCLIQUES_HPP
#define PANGOLIN_GENCLIQUES_HPP
#pragma GCC optimize("Ofast")
#include <execution>
#include <iostream>
#include <set>
#include "GenAlters.hpp"
#include "Types.hpp"
std::set<Nodelist> GenCliques(const Altermap& altermap) {
    std::set<Nodelist>  cliques;
    std::for_each(std::execution::par_unseq, cRANGE(altermap), [&cliques, &altermap](const auto& node_alter) { /* loop through altermap */
        if(node_alter.second.size() > 1)  {                                                 /* find nodes with mulitple alters - binary relations aren't cliques */
            const auto&     alters          (node_alter.second);                            /* get the set of alters for those nodes */
            Nodelist        alter_alters_raw;                                               /* create a vector to hold */
            std::for_each(std::execution::unseq, cRANGE(alters),                            /* loop through the alters */
                [&alters, &alter_alters_raw, &node_alter, &altermap](const auto& alter) {   /* loop through the alters of those alters */
                    std::for_each(std::execution::unseq, cRANGE(altermap.at(alter)), 
                        [&alters, &node_alter, &alter_alters_raw](const auto& alt_alt) {   
                            if((alt_alt == node_alter.first) || ((std::find(std::execution::unseq, cRANGE(alters), alt_alt)) != alters.end())) {
                                alter_alters_raw.emplace_back(alt_alt); } }); });           /* Filter for the intersection between the node, its alters, its alters' alters - the clique */
            Nodelist        alter_alters    (SquishNodelist(alter_alters_raw));
            if(alter_alters.size() > 1) { cliques.emplace(alter_alters); } } });
    return cliques; }
#endif//PANGOLIN_GENCLIQUES_HPP