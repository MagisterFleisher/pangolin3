// #pragma  GCC optimize("Ofast")
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include "CSV.hpp"
#include "Degree.hpp"
#include "AlterHash.hpp"
#include "TriadGen.hpp"

int main(int argc, char* argv[]) {
    const std::string           file_name       (argv[1]);
    const std::uint8_t          skip_lines      (static_cast<std::uint8_t> (std::stoi(argv[2], nullptr, 10)) );  /* how many lines to skip at beginning of csv */
    const std::uint8_t          base_read       (static_cast<std::uint8_t> (std::stoi(argv[3], nullptr, 10)) );
    // const std::uint8_t          base_write      (static_cast<std::uint8_t> (std::stoi(argv[4], nullptr, 10)) );
        std::cout << "Main: File: " << file_name << "\n"; std::cout << "Main: argc: " << argc << "\n";
    const Graph                 graph           (ReadGraph_CSV( file_name, skip_lines, base_read));
        std::cout << "Graph edges: " << graph.edges.size() << "\n"; std::cout << "Graph nodes: " << graph.nodes.size() << "\n";
    std::string                 write_file_name (file_name);
    // const auto                  er              (WriteGraph_CSV(graph, write_file_name, base_write));
    std::cout << "Calling Simple degree \n";
    const std::unordered_map    simple_degree   (SimpleDegree(  graph));
    std::cout << "Calling out degree \n";
    const std::unordered_map    out_degree      (OutDegree(     graph));
    std::cout << "Calling in degree \n";
    const std::unordered_map    in_degree       (InDegree(      graph));
    std::cout << "Calling Alter hash \n";
    const Alterhash             alter_hash      (AlterHash(     graph));
    std::cout << "Calling triad set\n";
    const auto&                 clique_set      (CliqueFind( alter_hash));
    for(const auto& clique : clique_set) {
        std::cout << "Clique: "
        for(const auto& node : clique) {
            std::cout << node << " "; }
        std::cout << "\n"; }
    /* std::cout << "Calling triad set\n";
    const auto&                 triad_set       (TriadGen( alter_hash)); */
    return 0; }