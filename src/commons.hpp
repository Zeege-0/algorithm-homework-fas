
#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define IC() std::cout << "Line " << __LINE__ << "\n";

namespace lzj {

using graph_t = std::vector<std::unordered_set<int>>;

template <typename T> std::vector<T> topk(const std::vector<T> &vec, int k) {
  std::priority_queue<int, std::vector<int>, std::greater<T>> pq;
  for (int i = 0; i < k; ++i) {
    pq.push(i);
  }
  for (int i = k; i < vec.size(); ++i) {
    if (vec[i] > vec[pq.top()]) {
      pq.pop();
      pq.push(i);
    }
  }
  std::vector<T> ret;
  ret.reserve(pq.size());
  while (!pq.empty()) {
    auto x = pq.top();
    pq.pop();
    ret.push_back(x);
  }
  return ret;
}

/**
 * Reads graph from file, the first line is number of verteces, following lines are (u, v) pairs
 * seperated by blank space
 *
 * @param filename filename
 * @return graph stored as adjacent list
 */
graph_t readGraph(const std::string &filename, int numVer) {
  try {
    std::ifstream fin(filename);
    if (!fin) {
      std::cout << "Error open " << filename << "\n";
      exit(1);
    }
    std::string line;
    graph_t graph(numVer);
    while (fin >> line) {
      int comma = line.find(',');
      int u = std::stoi(line.substr(0, comma));
      int v = std::stoi(line.substr(comma + 1));
      if (u != v) {
        graph[u].insert(v);
      }
    }
    fin.close();
    return graph;
  } catch (std::exception &e) {
    std::cout << "Error reading " << filename << ": " << e.what() << "\n";
    exit(1);
  }
  return {}; // never reach
}

void writeGraph(const std::string &filename, const graph_t &graph) {
  try {
    std::ofstream fout(filename);
    if (!fout) {
      std::cout << "Error open " << filename << "\n";
      exit(1);
    }
    // fout << graph.size() << "\n";
    for (int i = 0; i < graph.size(); ++i) {
      for (int j : graph[i]) {
        fout << i << "," << j << "\n";
      }
    }
  } catch (std::exception &e) {
    std::cout << "Error writing " << filename << ": " << e.what() << "\n";
    exit(1);
  }
}

int getNumEdges(const graph_t &graph) {
  int sum = 0;
  for (const auto &i : graph) {
    sum += i.size();
  }
  return sum;
}

// print out a container
template <class Os, class K> Os &operator<<(Os &os, const std::unordered_set<K> &v) {
  os << '[' << v.size() << "] {";
  bool o{};
  for (const auto &e : v)
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
    for (auto node : graph[i]) {
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
template <typename T> void printPageRank(const std::vector<T> &pageRank, std::ostream &oss = std::cout) {
  oss << std::fixed << std::setprecision(5);
  for (int i = 0; i < pageRank.size(); ++i) {
    oss << "Node " << i << ": " << pageRank[i] << std::endl;
  }
}
} // namespace lzj
