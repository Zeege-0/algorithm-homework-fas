
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include <unordered_map>


using graph_t = std::vector<std::unordered_set<int>>;


#define IC() std::cout << "Line " << __LINE__ << "\n";


// print out a container
template <class Os, class K>
Os& operator<<(Os& os, const std::unordered_set<K>& v) {
    os << '[' << v.size() << "] {";
    bool o{};
    for (const auto& e : v)
        os << (o ? ", " : (o = 1, " ")) << e;
    return os << " }\n";
}



/**
 * Print the graph stored as an adjacency list
 * 
 * @param graph graph
 * @param oss output stream, default to std::cout
 */
void printGraph(const graph_t &graph, std::ostream &oss = std::cout) {
  std::cout << "Graph {"; 
  for (int i = 0; i < graph.size(); i++) {
    oss << i << ": [";
    for (auto node: graph[i]) {
      oss << node << " ";
    }
    oss << "], ";
  }
  std::cout << "}\n";
}



/**
 * Print page rank
 * 
 * @param pageRank page rank
 * @param oss output stream, default to std::cout
*/
template<typename T>
void printPageRank(const std::vector<T> &pageRank, std::ostream &oss = std::cout) {
  oss << std::fixed << std::setprecision(5);
  for (int i = 0; i < pageRank.size(); ++i) {
    oss << "Node " << i << ": " << pageRank[i] << std::endl;
  }
}

