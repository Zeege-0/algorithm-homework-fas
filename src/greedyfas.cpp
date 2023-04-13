#include <fstream>
#include <iostream>
#include <vector>

#include "commons.hpp"
#include "indicators/indicators.hpp"

namespace cjy {

// Removing the sink affects the out-degree of other nodes
void removeSink(lzj::graph_t &graph, std::vector<bool> &eliminated, std::vector<int> &outdegree, int u) {
  // Find which node is connected to u
  for (int i = 0; i < (int)graph.size(); i++) {
    if (!eliminated[i]) {
      for (int j : graph[i]) {
        if (j == u) {
          outdegree[i]--;
        }
      }
    }
  }
}

// Removing the source will affect the in-degree of other nodes
void removeSource(lzj::graph_t &graph, std::vector<bool> &eliminated, std::vector<int> &indegree, int u) {
  for (int v : graph[u]) {
    if (!eliminated[v]) {
      indegree[v]--;
    }
  }
}

std::vector<int> _greedyfasLA(lzj::graph_t &graph) {
  const int n = graph.size();

  std::vector<int> s1, s2;
  std::vector<int> indegree(n, 0);
  std::vector<int> outdegree(n, 0);

  // state of nodes
  std::vector<bool> eliminated(graph.size(), false);
  // Number of remaining nodes
  int rest = n;

  // compute the in-degree and out-degree of each node
  for (int i = 0; i < n; i++) {
    for (int j : graph[i]) {
      indegree[j]++;
      outdegree[i]++;
    }
  }

  // if the graph is not empty
  indicators::ProgressBar bar{
      indicators::option::BarWidth{50},
      indicators::option::Start{" ["},
      indicators::option::End{"]"},
      indicators::option::PrefixText{"0 / " + std::to_string(rest)},
      indicators::option::ShowElapsedTime{true},
      indicators::option::ShowRemainingTime{true},
      indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}};
  while (rest != 0) {
    // sink: out-degree == 0
    for (int u = 0; u < n; u++) {
      if (!eliminated[u] && outdegree[u] == 0) {
        eliminated[u] = true;
        s2.push_back(u);
        rest--;
        // bar.set_progress(100 - 100. * rest / n);
        // bar.set_option(indicators::option::PrefixText(std::to_string(n - rest) + " / " + std::to_string(n)));
        removeSink(graph, eliminated, outdegree, u);
      }
    }
    // when all nodes are eliminated, exit loop
    if (rest == 0) {
      break;
    }

    // source: in-degree == 0
    for (int u = 0; u < n; u++) {
      if (!eliminated[u] && indegree[u] == 0) {
        eliminated[u] = true;
        s1.push_back(u);
        rest--;
        // bar.set_progress(100 - 100. * rest / n);
        // bar.set_option(indicators::option::PrefixText(std::to_string(n - rest) + " / " + std::to_string(n)));
        removeSource(graph, eliminated, indegree, u);
      }
    }
    // when all nodes are eliminated, exit loop
    if (rest == 0) {
      break;
    }

    // find the node with maximum δ(u)
    int u_max = -1, delta_max = -1;
    for (int u = 0; u < n; u++) {
      if (!eliminated[u]) {
        // δ(u) = outdegree(u) - indegree(u)
        int delta = outdegree[u] - indegree[u];
        if (delta > delta_max) {
          delta_max = delta;
          u_max = u;
        }
      }
    }
    s1.push_back(u_max);
    removeSink(graph, eliminated, outdegree, u_max);
    removeSource(graph, eliminated, indegree, u_max);
    eliminated[u_max] = true;
    rest--;
    bar.set_progress(100 - 100. * rest / n);
    bar.set_option(indicators::option::PrefixText(std::to_string(n - rest) + " / " + std::to_string(n)));
  }

  std::vector<int> s;
  s.insert(s.end(), s1.begin(), s1.end());
  s.insert(s.end(), s2.rbegin(), s2.rend());

  return s;
}
lzj::graph_t readFromFile(const std::string filename) {
  std::ifstream in(filename);
  if (!in) {
    std::cout << "Error open " << filename << "\n";
    exit(1);
  }
  int num, u, v;
  in >> num;
  lzj::graph_t graph(num);
  while (in >> u >> v) {
    graph[u].insert(v);
  }
  in.close();
  return graph;
}
lzj::graph_t LAtoFAS(const std::vector<int> &la, const lzj::graph_t &graph) {
  // save the order of nodes in LA
  std::vector<int> orders(la.size());
  lzj::graph_t fas(graph.size());
  for (int i = 0; i < la.size(); i++) {
    orders[la[i]] = i;
  }
  for (int u = 0; u < graph.size(); ++u) {
    for (auto v : graph[u]) {
      if (orders[u] > orders[v]) {
        fas[u].insert(v);
      }
    }
  }
  return fas;
}

lzj::graph_t greedyFAS(lzj::graph_t &graph) {
  auto la = _greedyfasLA(graph);
  return LAtoFAS(la, graph);
}

void saveLAtofile(std::vector<int> &la, const std::string &filename) {
  std::ofstream out(filename);
  for (int u : la) {
    out << u << " ";
  }
  out.close();
}
std::vector<int> readLAFromFile(const std::string &filename) {
  std::vector<int> la;
  std::ifstream in(filename);
  int u;
  while (in >> u) {
    la.push_back(u);
  }
  in.close();
  return la;
}
void saveFAStofile(std::vector<std::pair<int, int>> &fas, const std::string &filename) {
  std::ofstream out(filename);
  for (auto [u, v] : fas) {
    out << u << " " << v << std::endl;
  }
  out.close();
}

} // namespace cjy
