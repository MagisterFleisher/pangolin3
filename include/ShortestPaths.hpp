#ifndef PANGOLIN_SHORTESTPATHS_HPP
#define PANGOLIN_SHORTESTPATHS_HPP
#include <folly/FBVector.h>
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
    return std::visit(Eq{}, lhs, rhs); }

//////////////////////////////////////////////////////////

struct Tree {
    ID edge_id;
    Node from;
    Node to;
    Path& root;
    std::vector<Tree>& branches; }

Path ShortestPath(Graph graph, Node start, Node finish, Altermap altermap) {
}

Path ShortestPath(Graph graph, Node start, Node finish) {
    Tree start_tree ({.from = start });
    Tree end_tree ({.from = finish });
    /* INIT */
    do {
        for(const auto& edge : graph.edges) {
            if(start_tree.from == edge.from) {
                start_tree.edge_id = edge.id;
                start_tree.to = edge.to;
                start_tree.root {.id = edge.id, }
            }
        }
        start_tree.id 
        GenAlters(graph, )
    } while ( );
}


// Unweighted Shortest Path For All Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph) {}

// Weighted Shortest Path Between Two Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph, Attributes weights, const Node& start, const Node& end) {}

// Weighted Shortest Path For All Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph, Attributes weigsts) {}

#endif //PANGOLIN_SHORTESTPATHS_HPP