#ifndef PANGOLIN_CSV_HPP
#define PANGOLIN_CSV_HPP

#include <algorithm>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Types.hpp"
#include "NodelistGen.hpp"
#include "HeaderMain.hpp"

Edge ParseLine(const std::string& line, const std::uint8_t base) {
    Edge edge;
    switch(base) {
        case 8: {
            std::sscanf(line.c_str(), "%lo,%lo,%lo", &edge.id, &edge.from, &edge.to);
            break; };
        case 10: {
            std::sscanf(line.c_str(), "%lu,%lu,%lu", &edge.id, &edge.from, &edge.to);
            break; };
        case 16: {
            std::sscanf(line.c_str(), "%lx,%lx,%lx", &edge.id, &edge.from, &edge.to);
            break; };
        default: {
            std::cerr << "Problem reading base of csv.\n";
            break; } }
    return edge; }

Graph Read_CSV(const std::string& file_name, const int& skip_lines, const std::uint8_t base) { std::cout << "Called Read_CSV" << "\n";
    const auto&         path            ("/home/aaron/Documents/cpp/pangolin3/data/");
    const auto&         csv_ext         ("_edges.csv");
    const auto&         full_name       ((path + file_name) + csv_ext);
    std::ifstream       csv             (full_name);
    Graph               graph;
    std::string         line;
    if(csv.fail()) { 
        auto err ("Read_CSV: Error opening file ");
        auto err_name (full_name);
        auto err_message (err + err_name);
        std::cerr << err_message << "\n";
        exit(1); } /* Check if file can open.  Exit with error if not.  */
    if(skip_lines > 0) {
        for(int i = 0; i < skip_lines; i++) { csv.ignore(10,'\n'); } } /* When specified, Ignore the first n lines of the CSV file. */
    while(std::getline(csv, line)) { 
        std::shared_ptr<Edge> edge (new Edge (ParseLine(line, base)));
        graph.edges.emplace_back(edge); }
    graph.nodes = NodelistGen(graph.edges);
    return graph; }

std::optional<std::string> WriteGraphStream_CSV(const std::string& file_buffer, const std::string& file_name) { std::cout << "\tCalled WriteGraphStream_CSV\n";
    std::ofstream                       outCSVFile          ( file_name, std::ios::out);
    if( outCSVFile.is_open()) {
        outCSVFile << file_buffer.c_str();
        outCSVFile.close();
        return std::nullopt;
    } else { return ("WriteGraphStream_CSV: Error opening" + file_name);} }

std::optional<std::string> WriteGraph_CSV(std::unique_ptr<Graph>& g, std::string& file_name, std::uint8_t base) { std::cout << "\tCalled WriteGraph_CSV\n";
    std::stringstream                   edges_stream_buffer;
    std::stringstream                   nodes_stream_buffer;
    const std::string                   file_nodes_save     (("data/" + file_name) + "_nodes.csv");
    const std::string                   file_edges_save     (("data/" + file_name) + "_edges.csv");
    switch(base) {
        case 8:{
            for(const auto& edge : g->edges ) { 
                edges_stream_buffer << std::oct << edge->id << "," << std::oct << edge->from << "," << std::oct << edge->to << "\n"; }
            break; };
        case 10:{
            for(const auto& edge : g->edges ) { 
                edges_stream_buffer << edge->id << "," << edge->from << "," << edge->to << "\n"; }
            break; };
        case 16:{
            for( const auto& edge : g->edges ) { 
                edges_stream_buffer << std::hex << edge->id << "," << std::hex << edge->from << "," << std::hex << edge->to << "\n"; }
            break; };
        default:{std::cerr << "Problem finding base to write csv.\n";
                return "Problem finding base to write csv."; } }
    const auto& edge_err = WriteGraphStream_CSV( edges_stream_buffer.str(), file_edges_save);
    if(edge_err) {
        std::cerr << "WriteGraph_CSV: Error writing Edges CSV list.";
        return std::nullopt; }
        switch(base) {
            case 8:{
                for(auto& node : g->nodes ) { nodes_stream_buffer << std::hex << node << "\n";}
                break; };
            case 10:{
                for(auto& node : g->nodes ) { nodes_stream_buffer << std::hex << node << "\n";}
                break; };
            case 16:{
                for(auto& node : g->nodes ) { nodes_stream_buffer << std::hex << node << "\n";}
                break; };
            default:{
                std::cerr << "Problem finding base to write csv.\n";
                return "Problem finding base to write csv."; } }
    const auto& node_err = WriteGraphStream_CSV( nodes_stream_buffer.str(), file_nodes_save);
    if(node_err) {
        auto& err ("WriteGraph_CSV: Error writing Nodes CSV list.");
        std::cerr << err;
        return err; }
    return std::nullopt; }
#endif//PANGOLIN_CSV_HPP