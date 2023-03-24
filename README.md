
# Algorithm Homework: FAS

This repository is the unofficial implementation of the paper [Computing a Feedback Arc Set Using PageRank](https://doi.org/10.1007/978-3-031-22203-0_1), which is the homework for DCS5172@SYSU: Advanced Algorithm Design and Analysis (Spring 2023).

## Compilation

The project requires C++17 standard, as specified in `CMakeLists.txt`.

```bash
cmake -B build
cmake --build build
```

## Usage

After success compilation, a CLI executable can be found at `build/src/fas`, which is the main entrance of the project. Here is an example to run it on the data in `data/simple.txt`. See `build/src/fas --help` for detailed usage.

```bash
mkdir out
./build/src/fas data/simple.txt -a pagerank -o out/simple.txt -p

# Output: 
# [pagerank] FAS size: 2
# Graph {0: [], 1: [], 2: [3 ], 3: [], 4: [5 ], 5: [], 6: [], }
```

The `build/src/fas` executable is compiled from `src/main.cpp`, you can see the usages of APIs there.


## Testing

Add your test and name it as `test/test_*.cpp`. Recompile the project `cmake --build build`. The executable target can be found at `build/test/`.


