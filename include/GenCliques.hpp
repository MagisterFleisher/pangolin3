#ifndef PANGOLIN_GENCLIQUES_HPP
#define PANGOLIN_GENCLIQUES_HPP
#pragma GCC optimize("Ofast")
#include <execution>
#include <iostream>
#include <set>
#include "GenAlters.hpp"
#include "Types.hpp"
std::set<Nodelist> GenCliques(Altermap altermap) {
    std::set<Nodelist>  cliques;
    /* loop through altermap */
    std::for_each(std::execution::par_unseq, cRANGE(altermap), [&cliques, &altermap](const auto& node_alter) {
        /* find nodes with mulitple alters - binary relations aren't cliques */
        switch(node_alter.second.size()) { case 1: break; default:  {
            /* get the set of alters for those nodes */
            const auto&     alters          (node_alter.second);
            /* create a vector to hold */
            Nodelist        alter_alters_raw;
            /* loop through the alters */
            std::for_each(std::execution::unseq, cRANGE(alters),
            /* loop through the alters of those alters */
                [&alters, &alter_alters_raw, &node_alter, &altermap](const auto& alter) {
                    std::for_each(std::execution::unseq, cRANGE((altermap.at(alter))), 
                        [&alters, &node_alter, &alter_alters_raw](const auto& alt_alt) {   
                            if(((std::find(std::execution::unseq, cRANGE(alters), alt_alt)) != alters.end()) || (alt_alt == node_alter.first)) {
                            /* Filter for the intersection between the node, its alters, its alters' alters - the clique */
                            alter_alters_raw.emplace_back(alt_alt);}  }); });
            Nodelist        alter_alters    (SquishNodelist(alter_alters_raw));
            switch(alter_alters.size()) { case 1: break; default: { 
                cliques.emplace(alter_alters);  }  } } } });
    return cliques;}
#endif//PANGOLIN_GENCLIQUES_HPP