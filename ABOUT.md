# About this project/repository

This repository contains coding examples related to a 3-part webinar on C/C++ Memory Management.

The code in many of these examples intentionally exhibits bad behavior even though it compiles. Please take time to understand the code. Some parts of this code are useful for reuse, but others here simply illustrate bad code. Don't copy the bad parts!

For more information, contact info@doulos.com.

## Requirements

You should have the following tools installed.

- C++ compiler that support C++17 or better (e.g., g++ version 9.4 or clang++ 10.0)
- `cmake` version 3.21 or better
- `gdb` version 9.2 or better
- `make` or `ninja`
- `perl` and `bash` if using any of the scripts
- {fmt} library -- used for I/O in several places as a better alternative to streaming and sprintf

This project has been tested on the following configurations

  1. macos Ventura 13.3.1a running on MacBook Pro with Apple M1 Max (Arm64) **without GDB**
  2. Ubuntu 20.04.6 LTS running on `x86_64` (Intel Xeon CPU) with 1 core & 2G RAM
  3. WSL2 running Ubuntu 22.04.2 LTS running on a Dell XPS 15 9510 with i9-11900H (x86_64)

  

## Building on Linux/macos/WSL2

See [Requirements]

There are two approaches to building this project from a Linux or macos perspective:

1. Use some provided scripts (under `extern/bin`)
2. Do all the steps manually

### Using provided scripts

```bash
source setup.profile
build fmt
build -test
```

### Manual steps


```bash
# Setup (see setup.profile)
TOP_DIR="$(pwd)/CnCpp-MemoryManagement"
SRC_DIR="${TOP_DIR}"
BUILD_DIR="${TOP_DIR}/build/debug"
export CC CXX
CXX="g++"
CC="gcc"

# Fetch source or download and unzip
git clone https://github.com/Doulos/CnCpp-MemoryManagement.git
cd "${TOP_DIR}"

# Change `fmt::format` calls to using streaming I/O or install the {fmt} library
# into `extern/` by cloning from GitHub
git clone https://github.com/fmtlib/fmt.git extern/fmt
cd extern/fmt
# Read and follow the installation instructions. Install under "${TOP_DIR}/extern"
cd -

# Configure
cmake "${SRC_DIR}" -B "${BUILD_DIR}" 

# Compile
cmake --build "${BUILD_DIR}"

# Run tests
ctest --test-dir build/debug -C Debug -VV
```
Depending on your environment, you may (if you're lucky) see errors or warnings about the issues this project exposes. If not, it simply proves the point that "code that compiles" may have subtle bugs.

<!--
# vim:nospell
-->
#### The end
