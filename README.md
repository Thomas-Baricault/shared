# tbaricault::shared

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue)

## Description

This is a C++23 library providing tools for shared libraries.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
    - [Download and install](#download-and-install)
    - [Uninstall](#uninstall)
    - [CMake](#cmake)
    - [Include](#include)
    - [Environment](#environment)
- [Documentation](#documentation)
- [Examples](#examples)
- [License](#license)

## Features

- Lib class
- Export and import macros

## Requirements

- C++23 or later
- CMake 3.20 or later

## Usage

### Download and install

```bash
git clone https://github.com/Thomas-Baricault/shared.git
cd shared
make install
```

### Uninstall

```bash
make uninstall
```

### CMake

Add the library to your project:

```cmake
find_package(tbaricault_shared REQUIRED)

target_link_libraries(
    my_target
    PRIVATE
        tbaricault::shared
)
```

### Include

```cpp
#include <tbaricault/shared.hpp>
```

### Environment

If you have a custom C++ installation, you can edit the `ENV` variable in the `Makefile` to specify your environment path.

Example on Windows with MSYS2/MinGW64:

```makefile
ENV = C:/msys64/mingw64
```

## Documentation

Read the complete documentation at [https://docs.thomas-baricault.fr/shared](https://docs.thomas-baricault.fr/shared).

## Examples

For an example library named `mylib`.

### Mylib

#### Architecture

```text
mylib/
├── myfunc.cpp
├── myfunc.hpp
├── mylib.hpp
├── myvar.cpp
├── myvar.hpp
└── share.hpp
```

#### `mylib.hpp`

Entrypoint for the library.

```cpp
#pragma once


#include "myfunc.hpp"
#include "myvar.hpp"
```

#### `share.hpp`

This header will allow all the code in your library to know the sharing mode for your exported symbols.

Replace `MYLIB` by your library identifier.

```cpp
#pragma once


#include <tbaricault/shared.hpp>


#ifdef BUILD_MYLIB
    #define SHARE_MYLIB EXPORT
#else
    #define SHARE_MYLIB IMPORT
#endif
```

#### `myfunc.hpp`

Example of exported function.

Don't forgot the `#include "share.hpp"`.

```cpp
#pragma once


#include "share.hpp"


SHARE_MYLIB void myfunc(int i);
```

#### `myfunc.cpp`

You can either define `BUILD_MYLIB` at the beginning of each builded file (before including the associated .hpp file) you have or simply add the `-DBUILD_MYLIB` option to your compilation command.

```cpp
#define BUILD_MYLIB


#include <iostream>

#include "myfunc.hpp"


void myfunc(int i)
{
    std::cout << "Hello world! (" << i << ")" << std::endl;
    return;
}
```

#### `myvar.hpp`

Example of exported variable.

```cpp
#pragma once


#include "share.hpp"


SHARE_MYLIB int myvar;
```

#### `myvar.cpp`

```cpp
#define BUILD_MYLIB


#include "myvar.hpp"


int myvar = 73;
```

#### Build

```console
$ cd mylib
$ c++ -o myfunc.o -c myfunc.cpp
$ c++ -o myvar.o -c myvar.cpp
$ c++ -shared -o mylib.dll myfunc.o myvar.o
```

### Example of usage when linking the library

Don't forgot to place `mylib.so` or `mylib.dll` in the same directory as your executable or in `PATH`.

#### `main.cpp`

```cpp
#include <iostream>

#include "mylib/mylib.hpp"


int main()
{
    myfunc(73);
    std::cout << myvar << std::endl;

    return (0);
}
```

```console
$ c++ -o main.o -c main.cpp
$ c++ -o test main.o -Lmylib -lmylib
$ ./test
Hello world! (73)
73
```

### Example of usage when loading the library

Don't forgot to place `mylib.so` or `mylib.dll` in the same directory as your executable or in `PATH`.

#### `main.cpp`

```cpp
#include <iostream>
#include <tbaricault/shared.hpp>


int main()
{
#ifdef _WIN32
    tbaricault::shared::Lib lib("mylib.dll");
#else
    tbaricault::shared::Lib lib("mylib.so");
#endif

    if (!lib)
    {
        std::cout << "Failed to load the library" << std::endl;
        return (0);
    }

    auto myfunc = lib.getSymbol<void (*)(int)>("myfunc");

    if (!myfunc)
    {
        std::cout << "Failed to load myfunc" << std::endl;
        return (0);
    }

    myfunc(73);

    auto myvar = lib.getSymbol<int*>("myvar");

    if (!myvar)
    {
        std::cout << "Failed to load myvar" << std::endl;
        return (0);
    }

    std::cout << (*myvar) << std::endl;

    return (0);
}
```

```console
$ c++ -o main.o -c main.cpp
$ c++ -o test main.o -ltbaricault_shared
$ ./test
Hello world! (73)
73
```

## License

This project is licensed under the MIT License.

See [LICENSE](LICENSE) for details.
