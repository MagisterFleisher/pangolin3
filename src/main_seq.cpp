#pragma  GCC optimize("Ofast")
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include "GenAlters.hpp"
#include "GenCliques.hpp"
#include "CSV.hpp"
#include "Degree.hpp"
#include "PrestigeSimple.hpp"
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

int main(int argc, char* argv[]) {
    const std::string&          file_name           (argv[1]);
    const std::uint8_t&         skip_lines          (static_cast<std::uint8_t> (std::stoi(argv[2], nullptr, 10)) );  /* how many lines to skip at beginning of csv */
    const std::uint8_t&         base_read           (static_cast<std::uint8_t> (std::stoi(argv[3], nullptr, 10)) );
    // const std::uint8_t&          base_write      (static_cast<std::uint8_t> (std::stoi(argv[4], nullptr, 10)) );

    std::cout << "Main: File: " << file_name << "\n"; std::cout << "Main: argc: " << argc << "\n";

    Graph               graph                (ReadGraph_CSV( file_name, skip_lines, base_read));
    
    std::cout << "\nGraph edges: " << graph.edges.size() << "\n"; std::cout << "Graph nodes: " << graph.nodes.size() << "\n";

//    std::string               write_file_name       (file_name);
    // const auto&               write_err             (WriteGraph_CSV(graph, write_file_name, base_write));

    std::cout << "\nCalling Simple degree \n";
    const auto startTime1 (high_resolution_clock::now());
    const Attribute&          degree_both         (Degree(graph, both));
    const auto endTime1 (high_resolution_clock::now());
    print_results("Degree(graph, both)", startTime1, endTime1);
    
    std::cout << "\nCalling out degree\n";
    const auto startTime2 (high_resolution_clock::now());
    const Attribute&          degree_out           (Degree(graph, out));
    const auto endTime2 (high_resolution_clock::now());
    print_results("Degree(graph, out)", startTime2, endTime2);
    
    std::cout << "\nCalling in degree\n";
    const auto startTime3 (high_resolution_clock::now());
    const Attribute&          degree_in            (Degree(graph, in));
    const auto endTime3 (high_resolution_clock::now());
    print_results("Degree(graph, in)", startTime3, endTime3);

    std::cout << "\nCalling GenAllAlter\n";
    if(graph.graph_size != giant) {
    const auto startTime4 (high_resolution_clock::now());
    const Altermap&           altermap             (GenAllAlters(graph));
    const auto endTime4 (high_resolution_clock::now());
    print_results("GenAllAlters(graph)", startTime4, endTime4);

    std::cout << "\nCalling GenCliques\n";
    std::cout << "This may take a while..." << "\n";
    const auto& startTime5 (high_resolution_clock::now());
    const auto& cliques             (GenCliques(altermap));
    const auto& endTime5 (high_resolution_clock::now());
    print_results("GenCliques(altermap)", startTime5, endTime5);

    std::cout << "Calling PrestigeSimple simple_degree\n";
    const auto& startTime6 (high_resolution_clock::now());
    const auto& prestige_both (PrestigeSimple(altermap, degree_both));
    const auto& endTime6 (high_resolution_clock::now());
    print_results("PrestigeSimple(altermap, simple_degree)", startTime6, endTime6);

    std::cout << "Calling PrestigeSimple out_degree\n";
    const auto& startTime7 (high_resolution_clock::now());
    const auto& prestige_out   (PrestigeSimple(altermap, degree_out));
    const auto& endTime7 (high_resolution_clock::now());
    print_results("PrestigeSimple(altermap, out_degree)", startTime7, endTime7);

    std::cout << "Calling PrestigeSimple_all in_degree\n";
    const auto& startTime8 (high_resolution_clock::now());
    const auto& prestige_in   (PrestigeSimple(altermap, degree_in));
    const auto& endTime8 (high_resolution_clock::now());
    print_results("PrestigeSimple(altermap, in_degree)", startTime8, endTime8);
    
    NodeAttributeTable node_attributes_table (graph.nodes.size());
    for(const auto& node : graph.nodes) {
        NodeAttributes node_att ({
            .node = node, 
            .DegreeBoth =   degree_both.at(node), 
            .DegreeIn =     degree_in.at(node), 
            .DegreeOut =    degree_out.at(node), 
            .PrestigeBoth = prestige_both.at(node), 
            .PrestigeIn  =  prestige_in.at(node),
            .PrestigeOut =  prestige_out.at(node) });
        node_attributes_table.emplace_back(node_att); }
    }
    return 0; }