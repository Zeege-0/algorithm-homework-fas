#include <iostream>
#include <vector>
#include <algorithm>

#include "argparse.hpp"

using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> adj[MAXN];
double pr[MAXN], diff[MAXN];

void pagerank() {
  double d = 0.85, eps = 1e-6;
  for (int i = 1; i <= n; i++)
    pr[i] = 1.0 / n;
  while (true) {
    bool done = true;
    for (int i = 1; i <= n; i++) {
      double sum = 0;
      for (int j : adj[i]) {
        sum += pr[j] / adj[j].size();
      }
      double new_pr = (1 - d) / n + d * sum;
      if (abs(pr[i] - new_pr) > eps) done = false;
      pr[i] = new_pr;
    }
    if (done) break;
  }
}

void feedback_arc_set() {
  for (int i = 1; i <= n; i++) {
    for (int j : adj[i]) {
      diff[j] += pr[i] / adj[i].size() - pr[j] / adj[j].size();
    }
  }
  vector<pair<double, pair<int, int>>> edges;
  for (int i = 1; i <= n; i++) {
    for (int j : adj[i]) {
      if (diff[j] > 0) {
        edges.push_back({diff[j], {i, j}});
      }
    }
  }
  sort(edges.rbegin(), edges.rend());
  vector<int> feedback_arc;
  for (auto edge : edges) {
    int u = edge.second.first, v = edge.second.second;
    if (find(feedback_arc.begin(), feedback_arc.end(), u) == feedback_arc.end() && find(feedback_arc.begin(), feedback_arc.end(), v) == feedback_arc.end()) {
      feedback_arc.push_back(v);
    }
  }
  for (int v : feedback_arc) {
    cout << v << " ";
  }
}

int main(int argc, char **argv) {
  argparse::ArgumentParser parser("test");
  parser.add_argument("-o", "--output")
      .required()
      .help("specify the output file.");

  parser.add_argument("square")
      .help("display the square of a given integer")
      .scan<'i', int>();

  try {
    parser.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    std::exit(1);
  }

  auto input = parser.get<int>("square");
  std::cout << (input * input) << std::endl;

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
  pagerank();
  feedback_arc_set();
  return 0;
}
