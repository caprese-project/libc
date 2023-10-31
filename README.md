# Caprese Standard C Library Template

Standard C library template for operating systems that run on the Caprese microkernel.

## How to Install

### Prerequisites

Before installing, make sure you have installed all of the following:

- CMake version 3.20 or higher
- Ninja

### Download the Source Code

You can download the source code from GitHub at https://github.com/caprese-project/libc

```sh
git clone https://github.com/caprese-project/libc
```

### Build and Install

Once you have the source code, you can build and install the library with the following commands:

```sh
cmake -B build -G Ninja -DCMAKE_C_COMPILER:FILEPATH=/path/to/your/c-compiler
cmake --build build
sudo cmake --install build
```

This will install the library to the default system location (e.g. /usr/local/). If you want to install it to a different location, you can use the --prefix option:

```sh
sudo cmake --install build --prefix /path/to/install/prefix
```

## How to Use



## Note

- This library is provided as a template, and developers can customize it as needed.
- Implementations such as string.h are OS-independent and are provided as a template, but OS-dependent parts need to be implemented by the developer.
