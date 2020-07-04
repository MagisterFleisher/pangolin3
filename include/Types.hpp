#ifndef PANGOLIN_TYPES_HPP
#define PANGOLIN_TYPES_HPP
#include <memory>
#include <string> 
#include <unordered_map>
#include <vector>

using ID = std::uint64_t;
// template<typename Id> using ID = ID<Id>;

// template<typename Id>
// extern ID ToID(std::string strID) { return ID<Id>(std::stoi(strID.c_str(), nullptr, 10));}
extern ID ToID(std::string strID) { return ID(std::stoi(strID.c_str(), nullptr, 10));}

typedef struct { ID id; } Node;
// template<Typename Id> using struct Node { ID<Id> id; };

// template<Typename Id> using struct Edge { ID<id> id; ID<id> from; ID<id> to; }
typedef struct {
    ID id;
    ID from;
    ID to;
} Edge;

// template<Typename Id> using struct Nodelist { std::vector<Id> nodes; };
// typedef std::vector<ID> Nodelist;
// using Nodelist = std::vector<ID>;
using Nodelist = std::vector<std::shared_ptr<ID>>;

// using Edgelist = std::vector<Edge>;
// typedef std::vector<Edge> Edgelist;
using Edgelist = std::vector<std::shared_ptr<Edge>>;

// using struct Graph {Edgelist edges; Nodelist nodes;}
typedef struct {
    Edgelist edges;
    Nodelist nodes; 
} Graph;

// typedef std::vector<std::vector<std::unique_ptr<Node>>> Adjacencylist;
// using Incidence_Matrix = mtl::dense2D<auto>;
// using Adjacancy_Matrix = mtl::dense2D<auto>;
/* typedef struct{
    std::unordered_map<ID, std::uint64_t> simple_degree;
    std::unordered_map<ID, std::uint64_t> in_degree;
    std::unordered_map<ID, std::uint64_t> out_degree;
    std::unordered_map<ID, std::uint64_t> betweenness;
    std::unordered_map<ID, std::uint64_t> eigencentrality;
    std::unordered_map<ID, std::uint64_t> page_rank;
    std::unordered_map<ID, std::uint64_t> closeness;
    std::unordered_map<ID, std::uint64_t> katz;
    std::unordered_map<ID, std::uint64_t> reach;
    std::unordered_map<ID, std::uint64_t> reach_efficiency;
    std::unordered_map<ID, std::uint64_t> micmac;
    std::unordered_map<ID, std::uint64_t> hits_hubs;
    std::unordered_map<ID, std::uint64_t> hits_authorities;
    std::unordered_map<ID, std::uint64_t> alpha;
    std::unordered_map<ID, std::uint64_t> power;
    std::unordered_map<ID, std::uint64_t> flow_betweenness;
    std::unordered_map<ID, std::uint64_t> load;
    std::unordered_map<ID, std::uint64_t> gil_schmidt;
    std::unordered_map<ID, std::uint64_t> information_centrality;
    std::unordered_map<ID, std::uint64_t> stress_centrality;
    std::unordered_map<ID, std::uint64_t> eccentricity;
    std::unordered_map<ID, std::uint64_t> radiality;
    std::unordered_map<ID, std::uint64_t> delta;
    // many more
    std::uint64_t density;
    std::uint64_t radius;
    std::uint64_t circumference;
}  GraphMetrics; */
#endif//PANGOLIN_TYPES_HPP