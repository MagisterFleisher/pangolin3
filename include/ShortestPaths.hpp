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

#endif //PANGOLIN_SHORTESTPATHS_HPP