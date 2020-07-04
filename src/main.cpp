#include <iostream>
#include <cassert>
#include <string>
#include <memory>
#include "HeaderMain.hpp"
#include "CSV.hpp"

int main(int argc, char* argv[]) {
    const std::string&          file_name       (argv[1]);
    const std::uint8_t&         skip_lines      (static_cast<std::uint8_t> (std::stoi(argv[2], nullptr, 10)) );  /* how many lines to skip at beginning of csv */
    const std::uint8_t&         base_read       (static_cast<std::uint8_t> (std::stoi(argv[3], nullptr, 10)) );
    const std::uint8_t&         base_write      (static_cast<std::uint8_t> (std::stoi(argv[4], nullptr, 10)) );
    std::cout << "Main: File: " << file_name << "\n";
    std::cout << "Main: argc: " << argc << "\n";
    std::unique_ptr<Graph>      graph           (new Graph (Read_CSV(file_name, skip_lines, base_read)));
    std::cout << "Graph edges: " << graph->edges.size() << "\n";
    std::cout << "Graph nodes: " << graph->nodes.size() << "\n";
    std::string                 write_file_name (file_name);
    auto                        er              (WriteGraph_CSV(graph, write_file_name, base_write));
    std::cout << std::endl;
    return 0; }