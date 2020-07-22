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
    
    const auto startTime (high_resolution_clock::now());
    const Graph&               graph                (ReadGraph_CSV( file_name, skip_lines, base_read));
    const auto endTime (high_resolution_clock::now());
    print_results("ReadGraph_CSV", startTime, endTime);

    std::cout << "\nGraph edges: " << graph.edges.size() << "\n"; std::cout << "Graph nodes: " << graph.nodes.size() << "\n";

    std::string               write_file_name       (file_name);

    // const auto&               write_err             (WriteGraph_CSV(graph, write_file_name, base_write));

    std::cout << "\nCalling Simple degree \n";
    const auto startTime1 (high_resolution_clock::now());
    const Attribute&          simple_degree         (Degree(graph, both));
    const auto endTime1 (high_resolution_clock::now());
    print_results("Degree(graph, both)", startTime1, endTime1);
    
    // for(const auto& degree : simple_degree) {
    //    std::cout << "Node: " << degree.first << " Simple Degree: " << degree.second << "\n"; }

    std::cout << "\nCalling out degree\n";
    const auto startTime2 (high_resolution_clock::now());
    const Attribute&          out_degree           (Degree(graph, out));
    const auto endTime2 (high_resolution_clock::now());
    print_results("Degree(graph, out)", startTime2, endTime2);
    
    // for(const auto& degree : out_degree) {
    //    std::cout << "Node: " << degree.first << " Out Degree: " << degree.second << "\n"; }

    std::cout << "\nCalling in degree\n";
    const auto startTime3 (high_resolution_clock::now());
    const Attribute&          in_degree            (Degree(graph, in));
    const auto endTime3 (high_resolution_clock::now());
    print_results("Degree(graph, in)", startTime3, endTime3);
    // for(const auto& degree : in_degree) {
    //    std::cout << "Node: " << degree.first << " In Degree: " << degree.second << "\n"; }

    std::cout << "\nCalling GenAllAlter\n";
    if(graph.graph_size != giant) {
    const auto startTime4 (high_resolution_clock::now());
    const Altermap&           altermap             (GenAllAlters(graph));
    const auto endTime4 (high_resolution_clock::now());
    print_results("GenAllAlters(graph)", startTime4, endTime4);

    const auto startTime5 (high_resolution_clock::now());
    const auto&                 cliques             (GenCliques(altermap));
    const auto endTime5 (high_resolution_clock::now());
    print_results("GenCliques(altermap)", startTime5, endTime5);

/*
    std::cout << "Calling PrestigeSimple_all\n";
    const auto&               prestige_simple_all   (PrestigeSimple(altermap, simple_degree));

    std::cout << "Calling PrestigeSimple_out\n";
    const auto&                prestige_simple_out  (PrestigeSimple(altermap, out_degree));

    std::cout << "Calling PrestigeSimple_in\n";
    const auto&                prestige_simple_in   (PrestigeSimple(altermap, in_degree)); */
    }
    return 0; }