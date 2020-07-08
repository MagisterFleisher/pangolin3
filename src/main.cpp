#pragma  GCC optimize("Ofast")
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include "AlterHash.hpp"
#include "CliqueFind.hpp"
#include "CSV.hpp"
#include "Degree.hpp"
#include "PrestigeSimple.hpp"

int main(int argc, char* argv[]) {
    const std::string&           file_name       (argv[1]);
    const std::uint8_t&          skip_lines      (static_cast<std::uint8_t> (std::stoi(argv[2], nullptr, 10)) );  /* how many lines to skip at beginning of csv */
    const std::uint8_t&          base_read       (static_cast<std::uint8_t> (std::stoi(argv[3], nullptr, 10)) );
    std::cout << "Main: File: " << file_name << "\n"; std::cout << "Main: argc: " << argc << "\n";
    
    const Graph                 graph           (ReadGraph_CSV( file_name, skip_lines, base_read));
    std::cout << "Graph edges: " << graph.edges.size() << "\n"; std::cout << "Graph nodes: " << graph.nodes.size() << "\n";
    std::string                 write_file_name (file_name);
    
    std::cout << "Calling Simple degree \n";
    const Centrality&           simple_degree       (Degree(graph, both));

    std::cout << "Calling Alter hash \n";
    const Alterhash&            alter_hash          (AlterHash(graph));
    for(auto n : alter_hash) {
        std::cout << "Node: " << n.first << " Alter count: " << n.second.size() << "\n"; }

    std::cout << "Calling PrestigeSimple_all\n";
    const auto&                                     prestige_simple_all (PrestigeSimple(alter_hash, simple_degree));

    std::cout << "Calling out degree \n";
    const Centrality            out_degree          (Degree(graph, out));

    std::cout << "Calling PrestigeSimple_out\n";
    const auto&                                     prestige_simple_out (PrestigeSimple(alter_hash, out_degree));

    std::cout << "Calling in degree \n";
    const Centrality            in_degree           (Degree(graph, in));
    
    std::cout << "Calling PrestigeSimple_in\n";
    const auto&                                     prestige_simple_in  (PrestigeSimple(alter_hash, in_degree));

    return 0; }

    // for(const auto& node : prestige_simple) { std::cout << "Node: " << node.first << " Prestige: " << node.second << "\n"; }
    // const std::uint8_t          base_write      (static_cast<std::uint8_t> (std::stoi(argv[4], nullptr, 10)) );
    // const auto                  er              (WriteGraph_CSV(graph, write_file_name, base_write));
    /*std::cout << "Calling out degree \n";
    const std::unordered_map<Node, std::uint64_t>   out_degree          (OutDegree(     graph));
    std::cout << "Calling in degree \n";
    const std::unordered_map<Node, std::uint64_t>   in_degree           (InDegree(      graph)); 

    for(const auto& node : prestige_simple) {
         std::cout << "Node: " << node.first << " Prestige: " << node.second << "\n"; } */
    /* std::cout << "Calling triad set\n";
    const auto&                 clique_set      (CliqueFind( alter_hash)); */
    /* for(const auto& clique : clique_set) {
        std::cout << "Clique: ";
        for(const auto& node : clique) {
            std::cout << node << " "; }
        std::cout << "\n"; } */
    /* std::cout << "Calling triad set\n";
    const auto&                 triad_set       (TriadGen( alter_hash)); */