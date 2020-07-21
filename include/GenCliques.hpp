#ifndef PANGOLIN_GENCLIQUES_HPP
#define PANGOLIN_GENCLIQUES_HPP
#pragma GCC optimize("Ofast")
#include <execution>
#include <set>
#include "GenAlters.hpp"
#include "Types.hpp"
#include "Degree.hpp"
std::set<Nodelist> GenCliques(Altermap altermap) {
    std::set<Nodelist>  cliques;
    std::for_each(std::execution::par_unseq, cRANGE(altermap),              [&cliques, &altermap](const auto& node_alter) {
        switch(node_alter.second.size()) {  case 1: break; default:  {
        const auto&     alters          (node_alter.second);
        Nodelist        alter_alters_raw;
        std::for_each(std::execution::unseq, cRANGE(alters),                [&](const auto& alter) {
        std::for_each(std::execution::unseq, cRANGE((altermap.at(alter))),  [&alters, &node_alter, &alter_alters_raw](const auto& alt_alt) {
            if(((std::find(RANGE(alters), alt_alt)) != alters.end()) || (alt_alt == node_alter.first)) {
                        alter_alters_raw.emplace_back(alt_alt); }  }); });
        Nodelist        alter_alters    (SquishNodelist(alter_alters_raw));
        switch(alter_alters.size()) {       case 1: break; default: { cliques.emplace(alter_alters); } } } } });
    return cliques;}
#endif//PANGOLIN_GENCLIQUES_HPP