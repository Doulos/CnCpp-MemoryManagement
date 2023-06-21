# About this project/repository

This repository contains coding examples related to a 3-part webinar on C/C++ Memory Management.

The code in many of these examples intentionally exhibits bad behavior even though it compiles.

For more information, contact <mailto:info@doulos.com>.

## Building on Linux/macos/WSL2

See [Requirements]

```bash
# Fetch source or download and unzip
git clone https://github.com/Doulos/CnCpp-MemoryManagement.git

# Setup (see setup.profile)
export CC CXX
CXX="g++"
CC="gcc"
SRC_DIR=""
BUILD_DIR="build/debug"

# Configure
cmake -S "${SYSTEMC_SRC}" -B "${BUILD_DIR}" 

# Compile
cmake --build "${BUILD_DIR}"

# Run tests
ctest --test-dir build/debug -C Debug -VV
```
Depending on your environment, you may (if you're lucky) see errors or warnings about the issues this project exposes. If not, it simply proves the point that "code that compiles" may have subtle bugs.

## Requirements

Note: This project was tested on:

1. macos Ventura 13.3.1a running on MacBook Pro with Apple M1 Max (Arm64) **without GDB**
2. Ubuntu 20.04.6 LTS running on `x86_64` (Intel Xeon CPU) with 1 core & 2G RAM
3. WSL2 running Ubuntu 20.04.5 LTS running on a Dell XPS 15 9510 with i9-11900H (x86_64)
4. WSL2 running Ubuntu 22.04.2 LTS running on a Dell XPS 15 9510 with i9-11900H (x86_64)

You should have the following tools installed.

- C++ compiler that support C++17 or better (e.g., g++ version 9.4 or clang++ 10.0)
- `cmake` version 3.21 or better
- `gdb` version 9.2 or better
- `make` or `ninja`
- `perl` and `bash` if using any of the scripts

<!--
# vim:nospell
-->
#### The end
