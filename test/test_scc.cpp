
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

    auto scc = computeScc(graph);

    for(auto &&component: scc){
        for(auto i: component){
            std::cout << i << ", ";
        }
        std::cout << "\n";
    }

    return 0;
}
