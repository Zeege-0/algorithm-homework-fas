/**
 * Command Line Interface for This Project
 */

#include <chrono>

#include "argparse/argparse.hpp"
#include "commons.hpp"
#include "pgfas.cpp"
#include "sortfas.cpp"
#include "greedyfas.cpp"

namespace chrono = std::chrono;

int main(int argc, char **argv) {
  argparse::ArgumentParser parser("fas", "0.1.0", argparse::default_arguments::help);

  parser.add_argument("filename")
      .help("file containing the graph in (from to) format");
  parser.add_argument("-n", "--vertices")
      .required()
      .help("number of vertices in the graph");
  parser.add_argument("-a", "--algo")
      .required()
      .choice({"_", "greedy", "sort", "pagerank"})
      .help("algorithm to use [greedy | sort | pagerank]");
  parser.add_argument("-o", "--output")
      .required()
      .help("output file path");
  parser.add_argument("-s", "--skip")
      .help("skip factor for pagerank");
  parser.add_argument("-p", "--print")
      .implicit_value(true)
      .default_value(false)
      .help("print the result fas");

  parser.parse_args_noexcept(argc, argv);

  auto filename = parser.get("filename");
  auto algo = parser.get("algo");
  auto outname = parser.get("output");
  bool print = parser.get<bool>("print");
  int numNodes = std::stoi(parser.get("vertices"));
  int skipK = 10;
  if(parser.present("skip")){
    skipK = std::stoi(parser.get("skip"));
  }
  

  if((numNodes > 100) && print){
    std::cout << "# nodes > 100, graph will not print to stdout";
  }

  lzj::graph_t fas;

  auto end_timer = chrono::high_resolution_clock::now();
  auto start_timer = chrono::high_resolution_clock::now();

  if (algo == "greedy") {
    auto graph = lzj::readGraph(filename, numNodes);
    fas = cjy::greedyFAS(graph);
  } else if (algo == "sort") {
    auto graph = lkx::readGraph(filename, numNodes);
    fas = graph.computeFAS();
  } else if (algo == "pagerank") {
    auto graph = lzj::readGraph(filename, numNodes);
    outname = outname.substr(0, outname.size() - 4) + "-" + std::to_string(skipK) + ".txt";
    fas = lzj::pageRankFAS(graph, skipK);
  }

  end_timer = chrono::high_resolution_clock::now();
  auto duration_ms = chrono::duration_cast<chrono::microseconds>(end_timer - start_timer).count() / 1000;

  std::cout << "[" << algo << "] FAS size: " << lzj::getNumEdges(fas) << "\n";
  std::cout << "[" << algo << "] elapsed in " << duration_ms << " ms\n";
  lzj::writeGraph(outname, fas);
  if (print) {
    lzj::printGraph(fas);
  }


}
