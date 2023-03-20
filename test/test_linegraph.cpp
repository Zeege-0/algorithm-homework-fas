
#include "src/linegraph.cpp"


int main() {
  Graph graph = {
      {1, 2},
      {0, 2},
      {0, 1, 3},
      {2}};
  Graph lineGraph = createLineGraph(graph);

  printGraph(lineGraph);

  return 0;
}