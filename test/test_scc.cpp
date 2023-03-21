
#include "src/scc.cpp"

int main() {
    std::vector<std::vector<int>> graph = {
        {1},
        {2},
        {3},
        {0, 1},
        {},
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
