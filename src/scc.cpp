#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>


static void _tarjan(int u, const std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &scc,
            std::vector<int> &low, std::vector<int> &disc, std::stack<int> &stk,
            std::unordered_set<int> &onstack, int *foundat) {
  disc[u] = *foundat;
  low[u] = *foundat;
  *foundat += 1;
  stk.push(u);
  onstack.insert(u);
  for (auto i : graph[u]) {
    if (disc[i] == -1) {
      _tarjan(i, graph, scc, low, disc, stk, onstack, foundat);
      low[u] = std::min(low[u], low[i]);
    } else if (onstack.count(i))
      low[u] = std::min(low[u], disc[i]);
  }
  if (disc[u] == low[u]) {
    std::vector<int> scctem;
    while (1) {
      int v = stk.top();
      stk.pop();
      onstack.erase(v);
      scctem.push_back(v);
      if (u == v)
        break;
    }
    scc.push_back(scctem);
  }
}

auto computeScc(const std::vector<std::vector<int>> &G) {
  std::vector<int> disc(G.size(), -1);
  std::vector<int> low(G.size(), 0);
  std::vector<std::vector<int>> scc;
  std::unordered_set<int> onStack;
  std::stack<int> stk;
  int times = 1;

  for (int i = 0; i < G.size(); ++i) {
    if (disc[i] == -1) {
      _tarjan(i, G, scc, low, disc, stk, onStack, &times);
    }
  }

  return scc;
}
