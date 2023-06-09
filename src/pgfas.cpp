/**
 * PageRank Feedback Arc Set Algorithm
 *
 * @author lzj
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "commons.hpp"
#include "indicators/indicators.hpp"

namespace lzj {

/**
 * Find line graph's node from origin graph's edge, this is a stupid solution because
 * std::tuple<int, int> CANNOT be hashed
 */
struct EdgeToNode {
  // private:
  std::unordered_map<std::string, int> mp;
  std::unordered_map<int, std::tuple<int, int>> rmp;
  std::string makeId(int u, int v) const { return std::to_string(u) + "-" + std::to_string(v); }

public:
  int find(int u, int v) const { return mp.at(makeId(u, v)); }

  std::tuple<int, int> rfind(int i) { return rmp.at(i); }

  void add(int u, int v) {
    int id = mp.size();
    mp[makeId(u, v)] = id;
    rmp[id] = {u, v};
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
static void _createLineGraphDFS(int u, int in, const graph_t &G, graph_t &LG, const EdgeToNode &edgeToNode,
                                std::unordered_set<int> &visited) {
  visited.insert(u);
  for (auto v : G[u]) {
    auto out = edgeToNode.find(u, v);
    if (in >= 0) {
      LG[in].insert(out);
    }
    if (!visited.count(v)) {
      _createLineGraphDFS(v, out, G, LG, edgeToNode, visited);
    } else {
      for (auto w : G[v]) {
        LG[out].insert(edgeToNode.find(v, w));
      }
    }
  }
}

/**
 * Implementation of line graph construction in algorithm 3
 *
 * @param G graph
 * @return tuple of [LG, EdgeMap]
 */
auto createLineGraph(const graph_t &G) {
  int edges = 0;
  EdgeToNode edgeToNode;
  for (int u = 0; u < G.size(); ++u) {
    edges += G[u].size();
    for (auto v : G[u]) {
      edgeToNode.add(u, v);
    }
  }
  graph_t LG(edges);
  std::unordered_set<int> visited;
  for (int u = 0; u < G.size(); ++u) {
    if (!visited.count(u)) {
      _createLineGraphDFS(u, -1, G, LG, edgeToNode, visited);
    }
  }
  return std::make_tuple(LG, edgeToNode);
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
template <typename T = double>
std::vector<T> computePageRank(graph_t &graph, int maxIterations, T tolerance = 0.0001f) {
  int n = graph.size();
  T initialRank = 1.0 / n;
  std::vector<T> rank(n, initialRank);
  std::vector<int> outDegree(n, 1);
  std::vector<T> rankDivOutDegree(n);

  // Compute out degree of each node
#pragma unroll
  for (int i = 0; i < n; i++) {
    outDegree[i] += graph[i].size();
  }

  // Iterate until convergence or maximum iterations
#pragma unroll
  for (int iter = 0; iter < maxIterations; iter++) {
#pragma unroll
    for (int i = 0; i < n; ++i) {
      rankDivOutDegree[i] = rank[i] / outDegree[i];
    }

    // pass score to neighbors
    std::fill(rank.begin(), rank.end(), 0.0);
#pragma unroll
    for (int i = 0; i < n; ++i) {
      for (int neighbor : graph[i]) {
        rank[neighbor] += rankDivOutDegree[i];
      }
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
static void _tarjan(int u, const graph_t &graph, graph_t &scc, std::vector<int> &low, std::vector<int> &disc,
                    std::stack<int> &stk, std::unordered_set<int> &onstack, int *foundat) {
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
    std::unordered_set<int> scctem;
    while (1) {
      int v = stk.top();
      stk.pop();
      onstack.erase(v);
      scctem.insert(v);
      if (u == v) {
        break;
      }
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
auto computeScc(const graph_t &graph) {
  std::vector<int> disc(graph.size(), -1);
  std::vector<int> low(graph.size(), 0);
  graph_t scc;
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

/**
 * Creates a subgraph from given verteces
 *
 * @param scc verteces
 * @param graph stored as adjacent list
 * @param subgraph stored as adjacent list
 */
auto createSubgraph(graph_t &sub, const std::unordered_set<int> &scc, const graph_t &graph) {
  std::fill(sub.begin(), sub.end(), std::unordered_set<int>());
  for (auto i : scc) {
    for (auto node : graph[i]) {
      if (scc.count(node)) {
        sub[i].insert(node);
      }
    }
  }
  return sub;
}

/**
 * Function to perform DFS traversal of the graph to test if the graph has cycle
 *
 * @param u current vertex to search
 * @param visited visited vertex
 * @param parent from where the
 * @param graph stored as adjacent list
 * @return true if has cycle
 */
static bool _hasCycleDfs(int u, const graph_t &graph, std::unordered_set<int> &parents,
                         std::unordered_set<int> &visited) {
  visited.insert(u);
  for (auto v : graph[u]) {
    if (!visited.count(v)) {
      parents.insert(v);
      if (_hasCycleDfs(v, graph, parents, visited)) {
        return true;
      }
    } else if (parents.count(v)) {
      return true;
    }
  }
  parents.erase(u);
  return false;
}

/**
 * Check if a graph has cycle
 *
 * @param graph stored as adjacent list
 * @return true if has cycle
 */
bool hasCycle(const graph_t &graph) {
  std::unordered_set<int> dfsed;
#pragma unroll
  for (int i = 0; i < graph.size(); i++) {
    if (!dfsed.count(i)) {
      std::unordered_set<int> parents;
      std::unordered_set<int> visited;
      if (_hasCycleDfs(i, graph, parents, visited)) {
        return true;
      }
      dfsed.merge(visited);
    }
  }
  return false;
}

/**
 * Impelement PageRanFAS in Algorithm 5, this is the main entrance of this file
 *
 * @param graph stored as adjacent list, the graph would be modified
 * @return feedback arc set stored as adjacent list
 */
auto pageRankFAS(graph_t &graph, int skipK = 10) {
  graph_t fas(graph.size());
  graph_t subgraph(graph.size());
  indicators::ProgressBar bar{
      indicators::option::BarWidth{50},
      indicators::option::Start{" ["},
      indicators::option::End{"]"},
      indicators::option::PrefixText{"0 / 0 SCCs"},
      indicators::option::ShowElapsedTime{true},
      indicators::option::ShowRemainingTime{true},
      indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};
  while (hasCycle(graph)) {
    auto sccs = computeScc(graph);
    bar.set_progress(100. * sccs.size() / graph.size());
    bar.set_option(
        indicators::option::PrefixText{std::to_string(sccs.size()) + " / " + std::to_string(graph.size()) + " SCCs"});
    for (const auto &component : sccs) {
      if (component.size() <= 1) {
        continue;
      }
      createSubgraph(subgraph, component, graph);
      auto [lineGraph, edgeMap] = createLineGraph(subgraph);
      auto pr = computePageRank(lineGraph, 5);
      int kForTopk = 1;
      kForTopk = (component.size() / 1000) * skipK + 1;
      auto maxids = topk(pr, kForTopk);
      for (auto id : maxids) {
        auto [u, v] = edgeMap.rfind(id);
        fas[u].insert(v);
        graph[u].erase(v);
      }
    }
  }
  bar.set_progress(100);
  bar.set_option(
      indicators::option::PrefixText{std::to_string(graph.size()) + " / " + std::to_string(graph.size()) + " SCCs"});

  return fas;
}

} // namespace lzj
