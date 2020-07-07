#ifndef PANGOLIN_TYPES_HPP
#define PANGOLIN_TYPES_HPP
#pragma  GCC optimize("Ofast")
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

#define RANGE(x)    x.begin(),  x.end()
#define cRANGE(x)   x.cbegin(), x.cend()

using ID            = std::uint64_t;
ID ToID(std::string strID) { return ID(std::stoul(strID.c_str(), nullptr, 10));}
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
using Alterhash     = std::unordered_map<Node, std::set<Node>>;
#endif//PANGOLIN_TYPES_HPP