
#include "src/pagerank.cpp"

// Unit Test
int main() {
  std::vector<std::vector<int>> graph = {
      {1, 2},
      {0, 2},
      {0, 1, 3},
      {2}};

  double tolerance = 0.0001;
  int maxIterations = 5;

  auto pageRank = computePageRank(graph, tolerance, maxIterations);

  printPageRank(pageRank);

  return 0;
}
