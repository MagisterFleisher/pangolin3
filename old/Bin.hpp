#ifndef PANGOLIN_BIN_HPP
#define PANGOLIN_BIN_HPP
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

Graph ReadNodes_Bin(const std::string& file_name) {                               std::cout << "Called Read_Bin" << "\n";
    const auto          path            ("/home/aaron/Documents/cpp/pangolin3/data/");
    const auto          bin_ext         ("_nodes.bin");
    const auto          full_name       ((path + file_name) + bin_ext);
    std::ifstream       bin             (full_name, std::ios::in | std::ios::binary);
    Graph               graph;
    if(bin.fail()) {                                                              /* Check if file can open.  Exit with error if not.  */ 
        std::cerr << "\tRead_Bin: Error opening file " << full_name << "\n"; exit(1); }
    bin.read(reinterpret_cast<char *> (&graph.nodes), graph.nodes.size() * sizeof(graph.nodes));
    std::cout << "\tRead_Bin: File successfully read\n\tReturning graph\n";
    bin.close();
    return graph; }

Graph ReadEdges_Bin(const std::string& file_name) {                  std::cout << "Called Read_Bin" << "\n";
    const auto          path            ("/home/aaron/Documents/cpp/pangolin3/data/");
    const auto          bin_ext         ("_edges.bin");
    const auto          full_name       ((path + file_name) + bin_ext);
    std::ifstream       bin             (full_name, std::ios::in | std::ios::binary);
    Graph               graph;
    if(bin.fail()) {                                                                        /* Check if file can open.  Exit with error if not.  */ 
        std::cerr << "\tRead_Bin: Error opening file " << full_name << "\n"; exit(1); }
    bin.read(reinterpret_cast<char *> (&graph.edges), graph.edges.size() * sizeof(graph.edges));                                   std::cout << "\tRead_Bin: File successfully read\n\tCalling NodelistGen: Generating node list\n";
    graph.nodes = NodelistGen(graph.edges);                                                 std::cout << "\tNodelist size: " << graph.nodes.size() << "\n";
    std::cout << "\tRead_Bin: Node list successfully generated\nReturning graph\n";
    return graph; }

std::optional<std::string> WriteGraph_EdgesBin(Edgelist& edges, const std::string& file_name) { std::cout << "\tCalled WriteGraph_EdgesBin\n"; 
    const std::string&              file_edges_save     (("data/" + file_name) + "_edges.bin");
    std::ofstream                   out_edges_binFile   ( file_edges_save, std::ios::out | std::ios::binary);
    if( out_edges_binFile.is_open()) {
    out_edges_binFile.write(reinterpret_cast<char *>(&edges), edges.size() * sizeof(edges));
    out_edges_binFile.close(); 
    } else { std::cerr << "\tWriteGraphStream_Bin: Error opening " << file_edges_save << "\n"; } 
    return std::nullopt; }

std::optional<std::string> WriteGraph_NodesBin(Nodelist& nodes, const std::string& file_name) { std::cout << "\tCalled WriteGraph_NodesBin\n"; 
    const std::string&                  file_nodes_save     (("data/" + file_name) + "_nodes.bin");
    std::ofstream                       out_nodes_binFile   ( file_nodes_save, std::ios::out | std::ios::binary);
    if( out_nodes_binFile.is_open()) {
        out_nodes_binFile.write(reinterpret_cast<char *> (&nodes), nodes.size() * sizeof(nodes));
    out_nodes_binFile.close();
    } else { std::cerr << "\tWriteGraphStream_Bin: Error opening" << file_nodes_save << "\n";  }
    return std::nullopt; }

std::optional<std::string> WriteGraph_Bin(Graph& g, std::string& file_name) { std::cout << "\tCalled WriteGraph_Bin\n";
    const auto err_edges = WriteGraph_EdgesBin(g.edges, file_name);
    const auto err_nodes = WriteGraph_NodesBin(g.nodes, file_name);
    return std::nullopt; }
#endif//PANGOLIN_BIN_HPP