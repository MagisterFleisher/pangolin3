#pragma  GCC optimize("Ofast")
#include <future>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include "GenAlters.hpp"
#include "GenCliques.hpp"
#include "CSV.hpp"
#include "Degree.hpp"
#include "PrestigeSimple.hpp"
#include "SimplifyGraph.hpp"
#include <chrono>
#include <random>
#include <ratio>
#include <vector>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;

void print_results(const char *const tag, high_resolution_clock::time_point startTime, high_resolution_clock::time_point endTime) {
    printf("%s: Time: %fms\n", tag, duration_cast<duration<double, milli>>(endTime - startTime).count()); }

NodeAttributeTable GenAllNodeAttributes(const Graph& graph, const Altermap& altermap) {
    NodeAttributeTable      node_attributes_table   (graph.nodes.size());
    std::future<Attribute>  DegreeBoth              (std::async([&]() {    return Degree(graph, both);}));
    std::future<Attribute>  DegreeOut               (std::async([&]() {    return Degree(graph, out);}));
    std::future<Attribute>  DegreeIn                (std::async([&]() {    return Degree(graph, in);}));
    const Attribute&        degree_both             (DegreeBoth.get());
    std::future<Attribute>  PrestigeBoth            (std::async([&]() {    return PrestigeSimple(altermap, degree_both); }));
    const Attribute&        degree_out              (DegreeOut.get());
    std::future<Attribute>  PrestigeOut             (std::async([&]() {    return PrestigeSimple(altermap, degree_out); }));
    const Attribute&        degree_in               (DegreeIn.get());
    std::future<Attribute>  PrestigeIn              (std::async([&]() {    return PrestigeSimple(altermap, degree_in); }));
    const auto&             prestige_both           (PrestigeBoth.get());
    const auto&             prestige_out            (PrestigeOut.get());
    const auto&             prestige_in             (PrestigeIn.get());
    std::cout<<"Creating NodeAttributesTable"<<"\n";
    for(const auto& node : graph.nodes) {
        NodeAttributes node_att ({
            .node           =   node,
            .DegreeBoth     =   degree_both.at(     node), 
            .DegreeIn       =   degree_in.at(       node), 
            .DegreeOut      =   degree_out.at(      node), 
            .PrestigeBoth   =   prestige_both.at(   node), 
            .PrestigeIn     =   prestige_in.at(     node),
            .PrestigeOut    =   prestige_out.at(    node) });
        node_attributes_table.emplace_back(         node_att); }
    return node_attributes_table; }

int main(int argc, char* argv[]) {
    const std::string&                     file_name                (argv[1]);
    const std::uint8_t&                    skip_lines               (static_cast<std::uint8_t> (std::stoi(argv[2], nullptr, 10)) );  /* how many lines to skip at beginning of csv */
    const std::uint8_t&                    base_read                (static_cast<std::uint8_t> (std::stoi(argv[3], nullptr, 10)) );
    // const std::uint8_t&                  base_write             (static_cast<std::uint8_t> (std::stoi(argv[4], nullptr, 10)) );
    std::cout << "Main: File: " << file_name << "\n"; std::cout << "Main: argc: " << argc << "\n";
    Graph                                  raw_graph                    (ReadGraph_CSV( file_name, skip_lines, base_read));
    std::cout << "\nGraph edges: " << raw_graph.edges.size() << "\n"; std::cout << "Graph nodes: " << raw_graph.nodes.size() << "\n";
    Graph                                  graph                    (SimplifyGraph(raw_graph, undirected));
    std::cout << "\nSimplified Graph edges: " << graph.edges.size() << "\n"; std::cout << "nSimplified Graph nodes: " << graph.nodes.size() << "\n";
    // std::string                          write_file_name        (file_name);
    // const auto&                          write_err              (WriteGraph_CSV(graph, write_file_name, base_write));
    std::cout << "\nCalling GenAllAlter\n";
    if(graph.graph_size != giant) {
        const auto                         startTime1              (high_resolution_clock::now());
        const Altermap&                    altermap                (GenAllAlters(graph));
        const auto                         endTime1                (high_resolution_clock::now());
        print_results("GenAllAlters(graph)", startTime1, endTime1);
        std::future<NodeAttributeTable>    NodeAttsTable           (std::async([&]() {    return GenAllNodeAttributes(graph, altermap);}));
        std::future<std::set<Nodelist>>    Cliques                 (std::async([&]() {    return GenCliques(altermap);}));
        const auto&                        node_atts_table         (NodeAttsTable.get());
        std::cout << "Beginning Node Attributes Table and Cliques.... this may take time" << "\n";
        const auto&                        cliques                 (Cliques.get()); }
    return 0; }