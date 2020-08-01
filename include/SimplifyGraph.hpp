#ifndef PANGOLIN_SIMPLIFYGRAPH_HPP
#define PANGOLIN_SIMPLIFYGRAPH_HPP
#pragma GCC optimize("Ofast")
#include <execution>
#include <set>
#include "Types.hpp"
Graph SimplifyGraph(const Graph& graph, Directionality directionality) {
    /* BUILD GRAPH */
    Graph simple_graph;
    simple_graph.directionality = directionality;
    ID i (0);
    /* CREATE EDGES */
    switch(directionality) {
    case undirected: {
        std::set<std::set<Node>> edge_set;
        std::for_each(std::execution::unseq, cRANGE(graph.edges), [&edge_set](const auto& edge) {
            std::set<Node> nodes ({edge.from, edge.to});
            edge_set.emplace(nodes); });
        std::for_each(cRANGE(edge_set), [&i, &simple_graph](const auto& edge){
            Nodelist edge_vec (cRANGE(edge));
            Edge edge_write ({.id = i, .from = edge_vec[0], .to = edge_vec[1] });
            simple_graph.edges.emplace_back(edge_write); 
            ++i; }); break;}; 
    default: {
        std::set<Nodelist> edge_set;
        std::for_each(std::execution::unseq, cRANGE(graph.edges), [&edge_set](const auto& edge) {
            if(edge.from != edge.to) { 
                Nodelist nodes ({edge.from, edge.to});
                edge_set.emplace(nodes); } });
        std::for_each(cRANGE(edge_set), [&i, &simple_graph](const auto& edge){
            Edge edge_write ({.id = i, .from = edge[0], .to = edge[1] });
            simple_graph.edges.emplace_back(edge_write); 
            ++i; }); break;}; }
    switch(simple_graph.edges.size()) {
        case 0: {                       std::cerr << "ReadGraph_CSV: No edges.  That's a problem."; exit(1);};
        case 1 ... 500 : {              simple_graph.graph_size = tiny;    break; };
        case 501 ... 100'000 : {        simple_graph.graph_size = small;   break; };
        case 100'001 ... 30'000'000 : { simple_graph.graph_size = big;     break; };
        default : {                     simple_graph.graph_size = giant;   break; }; }
    /* COPY NODES   */
    // simple_graph.nodes = std::move(graph.nodes);
    simple_graph.nodes = GenNodelist(graph.edges);
    /* RETURN GRAPH */
    return simple_graph; }
#endif//PANGOLIN_SIMPLIFYGRAPH_HPP