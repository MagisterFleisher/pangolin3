#ifndef PANGOLIN_SHORTESTPATHS_HPP
#define PANGOLIN_SHORTESTPATHS_HPP
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
std::vector<Edgelist> ShortestPaths(const Graph& graph, const Node& start, const Node& end) {
    Alterhash alterhash;     /* When alter hash already generated */
    Nodelist start_alters   (alterhash[start]);
    Nodelist end_alters     (alterhash[start]);
    /* Perhaps add GenAlters(...) if alter hash does not exist */
    
    /* Proceed by find node in other node's alters */
    std::for_each(cRANGE(start_alters), [&end_alters](const auto& start_alter){ });
    /* Proceed by finding intersection of alters - Better conceptually */
    do {
        const auto&             result_size     ((alter_set_size > alts_alt_size) ? alts_alt_size : alter_set_size);
        Nodelist                intersect       (result_size);
        auto                    iterator        (std::set_intersection(cRANGE(alter_set), cRANGE(alts_alt), intersect.begin()));
        intersect.resize(iterator - intersect.begin());
        intersect.shrink_to_fit();
    } while (intersect.empty());
    if(!intersect.empty()) { }
    return adjacencylist;
}


// Unweighted Shortest Path For All Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph) {}

// Weighted Shortest Path Between Two Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph, Attributes weights, const Node& start, const Node& end) {}

// Weighted Shortest Path For All Nodes
// std::vector<Edgelist> ShortestPaths(const Graph& graph, Attributes weigsts) {}

#endif //PANGOLIN_SHORTESTPATHS_HPP