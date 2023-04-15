# Minimum Feedback Arc Set

中文文档 | [English](/README.md)

本文档是写给助教的。

前置需求：

- 支持C++ 17的编译器
- Python3解释器，用于运行测试和画图脚本

我们提供了一个在Ubuntu 22.04.1 LTS上使用gcc@7.5.0编译的的可执行文件，存放在`./build/src/fas`下，可以使用`./test.sh`来一键运行测试（使用该脚本时，请勿移动任何文件路径）。

提供这个可执行文件因为PPT要求这么做，但是为了避免各种奇怪的问题，**我们强烈推荐在本地编译**。本项目**不使用任何外部依赖**，只需要运行以下命令即可，经过测试在Linux和MacOS平台上都测试过可以成功编译运行：

```bash
# Compile the project
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
# Run the tests
sh ./test.sh
```


