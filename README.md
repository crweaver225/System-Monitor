# System-Monitor

![System Monitor](images/monitor.png)

## Description

A C++ application which monitors a linux system. The application keeps track of cpu usage, including which processes are utilizing the cpu the most, as well as memory usage and the uptime of the system. 

Graphical output is handled by the outcurses library. 

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts
