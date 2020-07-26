#ifndef PANGOLIN_TYPES_HPP
#define PANGOLIN_TYPES_HPP
#pragma  GCC optimize("Ofast")
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
// #include <folly/FBVector.h>
#define RANGE(x)        x.begin(),      x.end()
#define cRANGE(x)       x.cbegin(),     x.cend()
enum Direction {        in,     out,    both };
enum GraphSize {        giant,  big,    small,  tiny };
enum Directionality {   directed,       undirected };
using Integer       =   std::uint_fast64_t;
using ID            =   Integer;
using Node          =   ID;
using Nodelist      =   std::vector<Node>;
typedef struct {
    ID id; 
    Node from;
    Node to;        }   Edge;
// using Nodelist   =   folly::fbvector<Node>;
// using Edgelist   =   folly::fbvector<Edge>;
// using Path       =   folly::fbvector<Edge>;
//using Altermap    =   std::map<Node, Nodelist>;
using Edgelist      =   std::vector<Edge>;
using Altermap      =   std::map<Node, Nodelist>; /* In lieu of an adjacency list*/
using Path          =   std::vector<Edge>;
using Attribute     =   std::unordered_map<Node, Integer>;
typedef struct {
    GraphSize graph_size;
    Directionality directionaltiy (directed);
    Edgelist edges;
    Nodelist nodes; }   Graph;
typedef struct {
    Node                node;
    std::uint_fast64_t  DegreeBoth;
    std::uint_fast64_t  DegreeIn;
    std::uint_fast64_t  DegreeOut;
    std::uint_fast64_t  PrestigeBoth;
    std::uint_fast64_t  PrestigeIn;
    std::uint_fast64_t  PrestigeOut;
                    }   NodeAttributes;
using NodeAttributeTable = std::vector<NodeAttributes>;
#endif//PANGOLIN_TYPES_HPP