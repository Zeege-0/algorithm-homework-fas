/**
 * PageRank Feedback Arc Set
 * 
 * @author lzj
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <tuple>

#include "commons.hpp"



/**
 * Find line graph's node from origin graph's edge, this is a stupid solution because 
 * std::tuple<int, int> CANNOT be hashed
*/
struct EdgeToNode {
private:
  std::unordered_map<std::string, int> mp;
  std::string makeId(int u, int v) const {
    return std::to_string(u) + "-" + std::to_string(v);
  }

public:
  int find(int u, int v) const {
    return mp.at(makeId(u, v));
  }
  
  void add(int u, int v) {
    mp[makeId(u, v)] = mp.size();
  }
};



/**
 * Implement the DFS procedure in Algorithm 3
 * 
 * @param node current DFS node in origin graph
 * @param in incoming edge to this node
 * @param G origin graph
 * @param LG line grpah
 * @param edgeToNode maps the "edge" in origin graph to "node" in line graph
 * @param visited visited nodes
*/
static void _createLineGraphDFS(int u, int in, const std::vector<std::vector<int>> &G,
                                std::vector<std::vector<int>> &LG, const EdgeToNode &edgeToNode,
                                std::unordered_set<int> &visited) {
  visited.insert(u);
  for (auto v : G[u]) {
    auto out = edgeToNode.find(u, v);
    if (in >= 0) {
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
 * 
 * @param G graph
 * @return line graph L(G)
*/
std::vector<std::vector<int>> createLineGraph(const std::vector<std::vector<int>> &G) {
  int edges = 0;
  EdgeToNode edgeToNode;
  for (int u = 0; u < G.size(); ++u) {
    edges += G[u].size();
    for (auto v : G[u]) {
      edgeToNode.add(u, v);
    }
  }
  std::vector<std::vector<int>> LG(edges, std::vector<int>());
  std::unordered_set<int> visited;
  for (int u = 0; u < G.size(); ++u) {
    if (!visited.count(u)) {
      _createLineGraphDFS(u, -1, G, LG, edgeToNode, visited);
    }
  }
  return LG;
}



/**
 * Implementation of PageRank in algorithm 4
 * 
 * @param graph stored as adjacent list
 * @param tolerance stop criteria for convergence
 * @param maxIterations max iterations
 * 
 * @return page rank of the graph
*/
template <typename T = float>
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
 * Implementation of Tarjan algorithm to find strongly connected components
 * 
 * @param u current vertex to search
 * @param graph stored as adjacent list
 * @param scc strongly connected components
 * @param low i-th vertex lowest reachable vertex
 * @param disc i-th vertex's foundat value
 * @param stk stack to store searching vertex
 * @param onstack whether the vertex is on stack
 * @param foundat the time at which a vertex was discovered
*/
static void _tarjan(int u, const std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &scc,
                    std::vector<int> &low, std::vector<int> &disc, std::stack<int> &stk,
                    std::unordered_set<int> &onstack, int *foundat) {
  disc[u] = *foundat;
  low[u] = *foundat;
  *foundat += 1;
  stk.push(u);
  onstack.insert(u);
  for (auto i : graph[u]) {
    if (disc[i] == -1) {
      _tarjan(i, graph, scc, low, disc, stk, onstack, foundat);
      low[u] = std::min(low[u], low[i]);
    } else if (onstack.count(i))
      low[u] = std::min(low[u], disc[i]);
  }
  if (disc[u] == low[u]) {
    std::vector<int> scctem;
    while (1) {
      int v = stk.top();
      stk.pop();
      onstack.erase(v);
      scctem.push_back(v);
      if (u == v)
        break;
    }
    scc.push_back(scctem);
  }
}


/**
 * Compute strongly connected components
 * 
 * @param graph stored as adjacent list
 * @return scc where scc[i] contains all the vertex of the i-th scc
*/
auto computeScc(const std::vector<std::vector<int>> &graph) {
  std::vector<int> disc(graph.size(), -1);
  std::vector<int> low(graph.size(), 0);
  std::vector<std::vector<int>> scc;
  std::unordered_set<int> onStack;
  std::stack<int> stk;
  int times = 1;

  for (int i = 0; i < graph.size(); ++i) {
    if (disc[i] == -1) {
      _tarjan(i, graph, scc, low, disc, stk, onStack, &times);
    }
  }

  return scc;
}
