#ifndef PANGOLIN_CSV_HPP
#define PANGOLIN_CSV_HPP
// #pragma  GCC optimize("Ofast")
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include "Types.hpp"
#include "NodelistGen.hpp"
#include "CheckFile.hpp"

Edge ParseLine(const std::string& line, const std::uint8_t& base) {
    Edge edge;
    switch(base) {
        case 8:     { std::sscanf(line.c_str(), "%lo,%lo,%lo", &edge.id, &edge.from, &edge.to); break; };
        case 10:    { std::sscanf(line.c_str(), "%lu,%lu,%lu", &edge.id, &edge.from, &edge.to); break; };
        case 16:    { std::sscanf(line.c_str(), "%lx,%lx,%lx", &edge.id, &edge.from, &edge.to); break; };
        default:    { std::cerr << "Problem reading base of csv.\n"; break; } }
    return edge; }

Graph ReadGraph_CSV(const std::string& file_name, const int& skip_lines, const std::uint8_t base) { std::cout << "Called Read_CSV" << "\n";
    const auto          path            ("/home/aaron/Documents/cpp/pangolin3/data/");
    const auto          csv_ext         ("_edges.csv");
    const auto          full_name       ((path + file_name) + csv_ext);
    std::ifstream       csv             (full_name);
    Graph               graph;
    std::string         line;
    if(csv.fail()) {                                                                        /* Check if file can open.  Exit with error if not.  */ 
        auto            err             ("\tRead_CSV: Error opening file ");
        auto            err_name        (full_name);
        auto            err_message     (err + err_name);
        std::cerr << err_message << "\n"; exit(1); }                                                                          std::cout << "\tRead_CSV: File successfully opened\n\tSkipping "  << skip_lines << " lines\n";
    if(skip_lines > 0) { for(int i = 0; i < skip_lines; i++) {                              /* When specified, Ignore the first n lines of the CSV file. */
        csv.ignore(10,'\n'); } }                                                            std::cout << "\tRead_CSV: Begin reading file\n";
    while(std::getline(csv, line)) { graph.edges.emplace_back(ParseLine(line, base)); }     std::cout << "\tRead_CSV: File successfully read\n\tCalling NodelistGen: Generating node list\n";
    graph.nodes = NodelistGen(graph.edges);                                                 std::cout << "\tNodelist size: " << graph.nodes.size() << "\n";
                                                                                            std::cout << "\tRead_CSV: Node list successfully generated\nReturning graph\n";
    return graph; }

std::optional<std::string> WriteGraph_EdgesCSV(const Graph& g, const std::string& file_name, const std::uint8_t base) { std::cout << "\tCalled WriteGraph_EdgesCSV\n"; 
const std::string&                  file_edges_save     (("data/" + file_name) + "_edges.csv");
    std::ofstream                   out_edges_CSVFile   ( file_edges_save, std::ios::out);
    if( out_edges_CSVFile.is_open()) {
        switch(base) {
        case 8:{ for(const auto& edge : g.edges ) { 
            out_edges_CSVFile << std::oct << edge.id << "," << std::oct << edge.from << "," << std::oct << edge.to << "\n"; } break; };
        case 10:{ for(const auto& edge : g.edges ) { 
            out_edges_CSVFile << edge.id << "," << edge.from << "," << edge.to << "\n"; } break; };
        case 16:{ for( const auto& edge : g.edges ) { 
            out_edges_CSVFile << std::hex << edge.id << "," << std::hex << edge.from << "," << std::hex << edge.to << "\n"; } break; };
        default:{ std::cerr << "Problem finding base to write csv.\n"; return "Problem finding base to write csv."; } }
    out_edges_CSVFile.close(); 
    } else { std::cerr << "\tWriteGraphStream_CSV: Error opening " << file_edges_save << "\n"; } 
    return std::nullopt; }

std::optional<std::string> WriteGraph_NodesCSV(const Graph& g, const std::string& file_name, const std::uint8_t base) { std::cout << "\tCalled WriteGraph_NodesCSV\n"; 
    const std::string&                  file_nodes_save     (("data/" + file_name) + "_nodes.csv");
    std::ofstream                       out_nodes_CSVFile   ( file_nodes_save, std::ios::out);
    if( out_nodes_CSVFile.is_open()) {
        switch(base) {
        case 8:  { for(auto& node : g.nodes ) { out_nodes_CSVFile << std::oct << node << "\n";} break; };
        case 10: { for(auto& node : g.nodes ) { out_nodes_CSVFile << node << "\n";} break; };
        case 16: { for(auto& node : g.nodes ) { out_nodes_CSVFile << std::hex << node << "\n";} break; };
        default:{ std::cerr << "Problem finding base to write csv.\n"; return "Problem finding base to write csv."; } }
    out_nodes_CSVFile.close();
    } else { std::cerr << "\tWriteGraphStream_CSV: Error opening" << file_nodes_save << "\n";  }
    return std::nullopt; }

std::optional<std::string> WriteGraph_CSV(Graph& g, std::string& file_name, std::uint8_t base) { std::cout << "\tCalled WriteGraph_CSV\n";
    const auto err_edges = WriteGraph_EdgesCSV(g, file_name, base);
    const auto err_nodes = WriteGraph_NodesCSV(g, file_name, base);
    return std::nullopt; }
#endif//PANGOLIN_CSV_HPP