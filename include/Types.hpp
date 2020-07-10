#ifndef PANGOLIN_TYPES_HPP
#define PANGOLIN_TYPES_HPP
#pragma  GCC optimize("Ofast")
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <folly/FBVector.h>

#define RANGE(x)    x.begin(),  x.end()
#define cRANGE(x)   x.cbegin(), x.cend()

using ID            = std::uint_fast64_t;
using Node          = ID;
using Nodelist      = folly::fbvector<Node>;
// using Nodelist      = std::vector<Node>;
typedef struct {
    ID id; 
    Node from;
    Node to;        } Edge;
using Edgelist      = folly::fbvector<Edge>;
// using Edgelist      = std::vector<Edge>;
typedef struct {
    GraphSize graph_size;
    Edgelist edges;
    Nodelist nodes; } Graph;
using Altermap      = std::unordered_multimap<Node, Node>; /* In leu of an adjacency list*/
using Path          = folly::fbvector<Edge>;
//using Altermap      = std::map<Node, Nodelist>;
using Attribute     = std::unordered_map<Node, std::uint64_t>;
enum Direction { in, out, both };
enum GraphSize { giant, big, small, tiny };
#endif//PANGOLIN_TYPES_HPP