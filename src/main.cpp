/**
 * Command Line Interface for This Project
 */

#include "argparse/argparse.hpp"
#include "commons.hpp"
#include "pgfas.cpp"

int main(int argc, char **argv) {
  argparse::ArgumentParser parser("fas", "0.1.0", argparse::default_arguments::help);

  parser.add_argument("filename")
      .help("file containing the graph in (from to) format");
  parser.add_argument("-a", "--algo")
      .required()
      .choice({"greedy", "sort", "pagerank"})
      .help("algorithm to use [greedy | sort | pagerank]");
  parser.add_argument("-o", "--output")
      .required()
      .help("output file path");
  parser.add_argument("-p", "--print")
      .implicit_value(true)
      .default_value(false)
      .help("print the result fas");

  parser.parse_args_noexcept(argc, argv);

  auto filename = parser.get("filename");
  auto algo = parser.get("algo");
  auto outname = parser.get("output");
  bool print = parser.get<bool>("print");

  graph_t fas;
  graph_t graph = readGraph(filename);

  if (algo == "greedy") {
    std::cout << "Not implemented\n";
  } else if (algo == "sort") {
    std::cout << "Not implemented\n";
  } else if (algo == "pagerank") {
    fas = pageRankFAS(graph);
  }

  std::cout << "[" << algo << "] FAS size: " << getNumEdges(fas) << "\n";
  writeGraph(outname, fas);
  if (print) {
    printGraph(fas);
  }
}
