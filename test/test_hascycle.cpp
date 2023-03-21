
#include "src/pgfas.cpp"

// Example usage
int main() {
    int n = 5;
    graph_t adj_list(n);
    adj_list[0].insert(1);
    adj_list[1].insert(2);
    adj_list[2].insert(4);
    adj_list[2].insert(3);
    adj_list[3].insert(4);
    adj_list[4].insert(1);

    if (hasCycle(adj_list))
        std::cout << "Graph has a cycle" << std::endl;
    else
        std::cout << "Graph does not have a cycle" << std::endl;

    return 0;
}
