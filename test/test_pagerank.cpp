
#include "src/pgfas.cpp"

// Unit Test
int main() {
  graph_t graph = {
      {1, 2},
      {0, 2},
      {0, 1, 3},
      {2}};

  double tolerance = 0.0001;
  int maxIterations = 5;

  auto pageRank = computePageRank(graph, maxIterations, tolerance);

  printPageRank(pageRank);

  return 0;
}
