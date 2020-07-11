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
    const std::string&          file_name           (argv[1]);
    const std::uint8_t&         skip_lines          (static_cast<std::uint8_t> (std::stoi(argv[2], nullptr, 10)) );  /* how many lines to skip at beginning of csv */
    const std::uint8_t&         base_read           (static_cast<std::uint8_t> (std::stoi(argv[3], nullptr, 10)) );
    // const std::uint8_t&          base_write      (static_cast<std::uint8_t> (std::stoi(argv[4], nullptr, 10)) );

    std::cout << "Main: File: " << file_name << "\n"; std::cout << "Main: argc: " << argc << "\n";
    
    const Graph               graph                 (ReadGraph_CSV( file_name, skip_lines, base_read));
    std::cout << "Graph edges: " << graph.edges.size() << "\n"; std::cout << "Graph nodes: " << graph.nodes.size() << "\n";
    std::string               write_file_name       (file_name);

    // const auto&                 write_err       (WriteGraph_CSV(graph, write_file_name, base_write));

    std::cout << "Calling Simple degree \n";
    const Attribute           simple_degree         (Degree(graph, both));

    std::cout << "Calling out degree \n";
    const Attribute            out_degree           (Degree(graph, out));


    std::cout << "Calling in degree \n";
    const Attribute            in_degree            (Degree(graph, in));

    std::cout << "Calling Alter hash \n";
    if(!(graph.graph_size == giant)) {
    const Altermap              altermap            (GenAllAlters(graph));

    std::cout << "Calling PrestigeSimple_all\n";
    const auto&               prestige_simple_all   (PrestigeSimple(altermap, simple_degree));

    std::cout << "Calling PrestigeSimple_out\n";
    const auto&                prestige_simple_out  (PrestigeSimple(altermap, out_degree));

    std::cout << "Calling PrestigeSimple_in\n";
    const auto&                prestige_simple_in   (PrestigeSimple(altermap, in_degree));
    }
    return 0; }