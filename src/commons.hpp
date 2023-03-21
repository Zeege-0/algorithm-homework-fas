
#include <iostream>
#include <iomanip>
#include <vector>


/**
 * Print the graph stored as an adjacency list
 * 
 * @param graph graph
 * @param oss output stream, default to std::cout
 */
void printGraph(const std::vector<std::vector<int>> &graph, std::ostream &oss = std::cout) {
  for (int i = 0; i < graph.size(); i++) {
    oss << i << ": ";
    for (int j = 0; j < graph[i].size(); j++) {
      oss << graph[i][j] << " ";
    }
    oss << "\n";
  }
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

