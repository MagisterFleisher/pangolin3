#pragma  GCC optimize("Ofast")
#include <iostream>
#include <string>
#include "CSV.hpp"

int main(int argc, char* argv[]) {
    const std::string           file_name       (argv[1]);
    const std::uint8_t          skip_lines      (static_cast<std::uint8_t> (std::stoi(argv[2], nullptr, 10)) );  /* how many lines to skip at beginning of csv */
    const std::uint8_t          base_read       (static_cast<std::uint8_t> (std::stoi(argv[3], nullptr, 10)) );
    const std::uint8_t          base_write      (static_cast<std::uint8_t> (std::stoi(argv[4], nullptr, 10)) );
        std::cout << "Main: File: " << file_name << "\n";
        std::cout << "Main: argc: " << argc << "\n";
    Graph                       graph           (Read_CSV(file_name, skip_lines, base_read));
        std::cout << "Graph edges: " << graph.edges.size() << "\n";
        std::cout << "Graph nodes: " << graph.nodes.size() << "\n";
    std::string                 write_file_name (file_name);
    const auto                  er              (WriteGraph_Bin(graph, write_file_name));
    std::cout << std::endl;
    return 0; }