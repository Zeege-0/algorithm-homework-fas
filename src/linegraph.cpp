
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <tuple>


using Graph = std::vector<std::vector<int>>;


/**
 * Find line graph's node from origin graph's edge, this is a stupid solution because 
 * std::tuple<int, int> CANNOT be hashed
 * @author lzj
*/
struct EdgeToNode{
private:
  std::unordered_map<std::string, int> mp;
  std::string makeId(int u, int v) const {
    return std::to_string(u) + "-" + std::to_string(v);
  }
public:
  int find(int u, int v) const {
    return mp.at(makeId(u, v));
  }
  void add(int u, int v){
    mp[makeId(u, v)] = mp.size();
  }
};


/**
 * Implement the DFS procedure in Algorithm 3
 * @author lzj
 * 
 * @param node current DFS node in origin graph
 * @param in incoming edge to this node
 * @param G origin graph
 * @param LG line grpah
 * @param edgeToNode maps the "edge" in origin graph to "node" in line graph
 * @param visited visited nodes
*/
static void _createLineGraphDFS(int u, int in, const Graph &G, Graph &LG, const EdgeToNode &edgeToNode,
                                std::unordered_set<int> &visited) {
  visited.insert(u);
  for (auto v : G[u]) {
    auto out = edgeToNode.find(u, v);
    if(in >= 0){
      LG[in].push_back(out);
    }
    if (!visited.count(v)) {
      _createLineGraphDFS(v, out, G, LG, edgeToNode, visited);
    } else {
      for (auto w : G[v]) {
        LG[out].push_back(edgeToNode.find(v, w));
      }
    }
  }
}


/**
 * Implementation of line graph construction in algorithm 3
 * @author lzj
 * 
 * @param G graph
 * @return line graph L(G)
*/
Graph createLineGraph(const Graph &G) {
  int edges = 0;
  EdgeToNode edgeToNode;
  for (int u = 0; u < G.size(); ++u) {
    edges += G[u].size();
    for(auto v: G[u]){
      edgeToNode.add(u, v);
    }
  }
  Graph LG(edges, std::vector<int>());
  std::unordered_set<int> visited;
  for(int u = 0; u < G.size(); ++u){
    if(!visited.count(u)){
      _createLineGraphDFS(u, -1, G, LG, edgeToNode, visited);
    }
  }
  return LG;
}

/**
 * Print the graph stored as an adjacency list
 * @author lzj
 * 
 * @param graph graph
 * @param oss output stream, default to std::cout
 */
void printGraph(const Graph &graph, std::ostream &oss = std::cout) {
  for (int i = 0; i < graph.size(); i++) {
    oss << i << ": ";
    for (int j = 0; j < graph[i].size(); j++) {
      oss << graph[i][j] << " ";
    }
    oss << "\n";
  }
}

