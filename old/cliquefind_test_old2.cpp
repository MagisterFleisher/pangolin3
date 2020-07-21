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
    Graph                       graph       (ReadGraph_CSV("ctsi", 1, 16));
    const auto&                 altermap    (GenAllAlters(graph)    );
    std::set<Nodelist> cliques;
    for(const auto& node_alter : altermap)                      {
        const auto&             alter_size  (node_alter.second.size());
        switch(alter_size) { case 1: break; default:            {
                Nodelist    clique;
                
                const auto&     node            (node_alter.first       );
                auto            alters          (node_alter.second      );
                Nodelist        alt_alter_list_raw;
                for(const auto& alter : alters)                 {
                    const auto& alter_alters    (altermap.at(alter)     );
                    const auto& alt_alt_size    (alter_alters.size()    );
                    switch(alt_alt_size) { case 1: break; default:  {
                        for(const auto& element_b : alter_alters)   {
                            alt_alter_list_raw.emplace_back(element_b); } } } }
                alters.emplace_back(node);
                const auto&     node_alter_list (SquishNodelist(alters));
                const auto&     alt_alterlist   (SquishNodelist(alt_alter_list_raw));
                                                                std::cout << "Node & Alters:\t";
                for(const auto& element_a : alters) {           std::cout << element_a << " "; }
                                                                std::cout << "\n\tAnd\n\t\t";
                for(const auto& element_c : alt_alterlist) {    std::cout << element_c << " "; }
                                                                std::cout << "\n\n\n";           } } }
    /*
    for(const auto& clique_print : cliques) {
        for(const auto& element_print : clique_print) {
            std::cout << element_print << " "; }
        std::cout << "\n"; }
    std::cout << "Cliques: " << cliques.size() << std::endl; */
    return 0; }