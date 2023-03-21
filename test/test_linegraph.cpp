
#include "src/pgfas.cpp"


int main() {
  std::vector<std::vector<int>> graph = {
      {1},
      {},
      {3},
      {0, 1},
      {},
      {6},
      {4}};
  auto lineGraph = createLineGraph(graph);

  printGraph(lineGraph);

  return 0;
}