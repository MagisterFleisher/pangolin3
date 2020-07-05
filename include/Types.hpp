#ifndef PANGOLIN_TYPES_HPP
#define PANGOLIN_TYPES_HPP
#include <memory>
#include <string>
#include <vector>
using ID            = std::uint64_t;
extern ID ToID(std::string strID) { return ID(std::stoi(strID.c_str(), nullptr, 10));}
// typedef struct {  ID id; } Node;
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
#endif//PANGOLIN_TYPES_HPP