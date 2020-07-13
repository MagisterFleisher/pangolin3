#include <set>
#include <vector>
#include <map>
#include <folly/FBVector.h>
#include "AlterHash.hpp"
#include "CSV.hpp"
#include "Types.hpp"
/*
from each node to every other node
n! paths
path length 1 is trivial  (alter hash)
path length 2 also trivial (alter hash of alterhash - nodes in first alterhash)
path length 3, path length 2 plus 1 (may have multiple shortest paths)
path length 4+, nontrivial
Dykstra's algorithm - should be parallelizable
Data: { set of 2 nodes : shortest path(s) between nodes }
shortest paths: unordered_map { set<Node> {N1, N2}, set<vector<Node>> {path} }
does the pair have a shortest path: { set<Node> {N1, N2}, path_length}
    if path_length < current path checking, skip
---
betweenness: for each node, sum of occurances in a shortest path set
- should be parallelizable */
/* 
 * Unweighted Shortest Path Between Two Nodes
 * 
 * Algorithm
 * start with two nodes
 * find alters for each node
 *      save alter pairs
 * find alters for alters
 *      save alter pairs
 * if alters in previous list, not shortest path, remove
 * Repeat 
 * When shortest paths from each node meet, there is the shortest path
 */
 /*
folly::fbvector<Path> ShortestPaths(const Graph& graph, const Node& start, const Node& end) {
    Path toward;
    folly::fbvector<ID> id_path;
    for(const auto graph : g.edges) {  }
    return adjacencylist; }

//////////////////////////////////////////////////////////

using Element = std::variant<A, B, C>;
struct Eq {
    template <typename T>
    bool operator()(T const& lhs, T const& rhs) const {
        return equalNode(lhs, rhs); }
    template <typename T, typename U>
    bool operator()(T const&, U const&) const {
        return false; } };
bool equalTree(Element const& lhs, Element const& rhs) {
    return std::visit(Eq{}, lhs, rhs); } */

//////////////////////////////////////////////////////////
/*
Path ShortestPath(Graph graph, Node start, Node finish) {
    Path path;
    if(start == finish) { 
        for(const auto& edge : graph.edges) {
            if((edge.from == start && edge.to == finish) || (edge.to == start && edge.from == finish)) {
                path.emplace_back(edge); } }
        return path; }
    std::set<std::pair<Node, Node>> paths;
    const auto&     start_alters    (GenAlters(graph, start));
    for(const auto& branch : start_alters) {
        paths.emplace(std::pair({branch.first, branch.second})); };
    const auto&     end_alters      (GenAlters(graph, finish));
    for(const auto& branch : paths) {
        std::cout << "\tNode: " << branch.first << "\t" << branch.second << "\n"; };
    std::cout << std::endl;
    return path; }
    /* 
    start_paths.emplace_back(AddBranches(graph, start));
    end_paths.emplace_back(AddBranches(graph, finish));
    for(const auto& branch : start_paths) {
        if(branch)
    }
    do {

    } while ( shortest_path == false );
} */

void Dijkstra(Graph graph, folly::fbvector<Nodelist> paths, Node start, Node finish) {
    Nodelist node_que (graph.nodes);
    for(const auto& edge : graph.edges) {
        if(edge.from == start || edge.to == start) {
            
        }
    }
    
    }




int main() {
    const Graph     graph           (ReadGraph_CSV("ctsi", 1, 16));
    std::cout << "Edges: " << graph.edges.size() << " Node: " << graph.nodes.size() << "\n";
    const auto&     shortest_path   (ShortestPath(graph, graph.nodes[5], graph.nodes[400]));
    //const Path      path        (ShortestPath(graph, 1, 8));
    return 0; }

// Unweighted Shortest Path For All Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph) {}

// Weighted Shortest Path Between Two Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph, Attributes weights, const Node& start, const Node& end) {}

// Weighted Shortest Path For All Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph, Attributes weigsts) {}

// #endif //PANGOLIN_SHORTESTPATHS_HPP