#pragma GCC optimize("Ofast")
#include <algorithm>
#include <execution>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <folly/FBVector.h>
#include "CSV.hpp"
#include "GenAlters.hpp"
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
int main() {
    Graph                   graph       (ReadGraph_CSV("ctsi", 1, 16));
    const auto&             altermap    (GenAllAlters(graph));
    std::set<Nodelist> cliques;
    for(const auto& node_alter : altermap) {
        const auto&         alter_size  (node_alter.second.size());
        switch(alter_size) {
            case 1: break;
            default: {
                Nodelist    clique;
                clique.emplace(node_alter.first);
                const auto& alters      (node_alter.second);
                for(const auto& alter : alters) {
                    const auto& alter_alters (altermap.at(alter)); }
                cliques.emplace(SquishNodelist(clique)); }  }  }
    for(const auto& clique_print : cliques) {
        for(const auto& element_print : clique_print) {
            std::cout << element_print << " "; }
        std::cout << "\n"; }
    std::cout << "Cliques: " << cliques.size() << std::endl;
    return 0; }