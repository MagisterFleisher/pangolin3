#include <algorithm>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string> 
#include <iostreams>
#include <unordered_map>
#include <vector>

using ID = std::uint64_t;
ID ToID(std::string strID) { return std::stoul(strID.c_str(), nullptr, 10);}
typedef struct {
    ID id;
} Node;
typedef std::vector<ID> Nodelist;
typedef struct {
    ID id;
    ID from;
    ID to;
} Edge;
typedef std::vector<Edge> Edgelist;
// typedef std::vector<std::vector<std::unique_ptr<Node>>> Adjacencylist;
// using Incidence_Matrix = mtl::dense2D<auto>;
// using Adjacancy_Matrix = mtl::dense2D<auto>;
std::vector<ID> NodelistGen(Edgelist& edges) {
    std::unordered_set<ID>  node_set;
    for(const auto& edge : edges ){
        node_set.insert( edge.from );
        node_set.insert( edge.to );}
    std::vector<ID>  nodes;
    std::copy(node_set.begin(), node_set.end(), nodes.begin());
    return nodes; }
typedef struct{
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
    std::uint64_t circumfirance;
}  GraphMetrics;
bool CheckFile(std::string full_name) {
    if(std::filesystem::is_character_file(full_name) && std::filesystem::exists(full_name)) {
        return true; } else {
        if(!std::filesystem::is_character_file(full_name)) {
            std::cerr << "CheckFile: Not character file: "  << full_name; }
        if(!std::filesystem::exists(full_name)) { 
            std::cerr << "CheckFile: Does not exist:     " << full_name; }
        return false; } }
Edge ParseLine(std::string line) {
    Edge edge;
    int i1, i2, i3;
    std::sscanf(line.c_str(), "%i,%i,%i", &i1, &i2, &i3);
    edge.id     = static_cast<std::uint64_t>(i1);
    edge.from   = static_cast<std::uint64_t>(i2);
    edge.to     = static_cast<std::uint64_t>(i3);
    return edge; }
Graph Read_CSV(std::string file_name, int skip_lines) {
    const auto&         path            ("../data/");
    const auto&         csv_ext         (".csv");
    const auto&         full_name       ((path + file_name) + csv_ext);
    std::ifstream       csv             (full_name);
    Graph               graph;
    std::string line;
    if(csv.fail()) { 
        std::cerr << "Read_CSV: Error opening file " << full_name; 
        exit(1); } /* Check if file can open.  Exit with error if not.  */
    if(skip_lines > 0) {
        for(int i = 0; i < skip_lines; i++) { csv.ignore(10,'\n'); } } /* When specified, Ignore the first n lines of the CSV file. */
    while(std::getline(csv, line)) { graph.edges.emplace_back(ParseLine(line)); }
    return graph; }    
std::optional<std::string> WriteGraphStream_CSV(std::stringstream &stream_buffer, const std::string& file_name) {
    std::cout << "\tCalled WriteGraphStream_CSV\n";
    std::ofstream                       outCSVFile          ( file_name, std::ios::out );
    const std::string                   file_buffer         ( stream_buffer.str() );
    if( outCSVFile.is_open()) {
        outCSVFile.write( file_buffer.c_str(), sizeof( file_buffer.c_str()) );
        outCSVFile.close();
        return std::nullopt;
        } else {
        return ("WriteGraphStream_CSV: Error opening" + file_name);} }
std::optional<std::string> WriteGraph_CSV(std::unique_ptr<Graph>& g, std::string& file_name) { 
    std::cout << "\tCalled WriteGraph_CSV\n";
    std::stringstream                   edges_stream_buffer;
    std::stringstream                   nodes_stream_buffer;
    const std::string                   file_nodes_save     (("data/" + file_name) + "_nodes.csv");
    const std::string                   file_edges_save     (("data/" + file_name) + "_edges.csv");
    for( const auto& edge : g->edges ) { 
        edges_stream_buffer << edge.id << "," << edge.from << "," << edge.to << "\n"; }
    const auto& edge_err = WriteGraphStream_CSV( edges_stream_buffer, file_edges_save);
    if(edge_err) { 
        std::cerr << "WriteGraph_CSV: Error writing Edges CSV list.";
        return std::nullopt; }
    for( const auto& node : g->nodes ) {
        nodes_stream_buffer << node << "\n"; }
    const auto& node_err = WriteGraphStream_CSV( nodes_stream_buffer, file_edges_save);
    if(node_err) { 
        std::cerr << "WriteGraph_CSV: Error writing Nodes CSV list.";
        return std::nullopt; }
    return std::nullopt; }