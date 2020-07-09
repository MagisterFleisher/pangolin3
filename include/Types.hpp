#ifndef PANGOLIN_TYPES_HPP
#define PANGOLIN_TYPES_HPP
#pragma  GCC optimize("Ofast")
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

#define RANGE(x)    x.begin(),  x.end()
#define cRANGE(x)   x.cbegin(), x.cend()

using ID            = std::uint_fast32_t;
using Node          = ID;
using Nodelist      = std::vector<Node>;
typedef struct { 
    ID id; 
    Node from;
    Node to;        } Edge;
using Edgelist      = std::vector<Edge>;
typedef struct {
    Edgelist edges;
    Nodelist nodes; } Graph;
using Adjacencylist = std::map<Node, Nodelist>;
using Altermap      = std::unordered_multimap<Node, Node>;
// using Altermap      = std::map<Node, Nodelist>;
using Attribute     = std::unordered_map<Node, std::uint64_t>;
enum Direction { in, out, both };
#endif//PANGOLIN_TYPES_HPP