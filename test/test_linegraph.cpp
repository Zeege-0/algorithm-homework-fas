
#include "src/pgfas.cpp"

using namespace lzj;

int main() {
  graph_t graph = {
      {1},
      {2},
      {3},
      {0, 1},
      {5},
      {6},
      {4}};
  auto [lineGraph, edgeMap] = createLineGraph(graph);

  printGraph(lineGraph);

  return 0;
}