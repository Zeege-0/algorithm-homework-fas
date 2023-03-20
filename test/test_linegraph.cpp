
#include "src/linegraph.cpp"


int main() {
  Graph graph = {
      {1},
      {},
      {3},
      {0, 1},
      {},
      {6},
      {4}};
  Graph lineGraph = createLineGraph(graph);

  printGraph(lineGraph);

  return 0;
}