
#include "src/pgfas.cpp"

// Example usage
int main() {
    int n = 5;
    std::vector<std::vector<int>> adj_list(n);
    adj_list[0].push_back(1);
    adj_list[1].push_back(2);
    adj_list[2].push_back(4);
    adj_list[2].push_back(3);
    adj_list[3].push_back(4);
    adj_list[4].push_back(1);

    if (hasCycle(adj_list))
        std::cout << "Graph has a cycle" << std::endl;
    else
        std::cout << "Graph does not have a cycle" << std::endl;

    return 0;
}
