
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>


/**
 * Implementation of PageRank in algorithm 4
 * @author lzj
 * 
 * @param graph stored as adjacent list
 * @param tolerance stop criteria for convergence
 * @param maxIterations max iterations
 * 
 * @return page rank of the graph
*/
template<typename T>
std::vector<T> computePageRank(std::vector<std::vector<int>> &graph, T tolerance, int maxIterations) {
  int n = graph.size();
  T initialRank = 1.0 / n;
  std::vector<T> rank(n, initialRank);
  std::vector<T> newRank(n, 0);
  std::vector<T> outDegree(n, 0);

  // Compute out degree of each node
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < graph[i].size(); j++) {
      outDegree[i]++;
    }
  }

  // Iterate until convergence or maximum iterations
  for (int iter = 0; iter < maxIterations; iter++) {
    T maxDiff = 0.0;

    // Compute new rank for each node
    for (int i = 0; i < n; i++) {
      newRank[i] = 0.0;
      for (int j = 0; j < graph[i].size(); j++) {
        int neighbor = graph[i][j];
        newRank[i] += rank[neighbor] / outDegree[neighbor];
      }
    }

    // Compute maximum difference between old and new ranks
    for (int i = 0; i < n; i++) {
      T diff = std::abs(newRank[i] - rank[i]);
      maxDiff = std::max(diff, maxDiff);
    }

    // Update rank with new rank
    std::copy(newRank.begin(), newRank.end(), rank.begin());

    // Check for convergence
    if (maxDiff < tolerance) {
      break;
    }
  }

  return rank;
}


/**
 * Print page rank
 * @author lzj
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

