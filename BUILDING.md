# Building Zenith

## Instructions

Steps to build Zenith from scratch for each operating system.

- [on Windows](#building-zenith-on-windows)
- [on Linux](#building-zenith-on-linux)
- [on macOS](#building-zenith-on-macos)


## Build System

Zenith uses the CMake build system.

Zenith doesn't allow in-source builds, so it is recommended to create a folder - usually build\ - and follow the instructions.

## Building Zenith on Windows

### Prerequisites

- CMake
- Git
- Visual Studio and C++ tools (Tested on VS2022)

It is important to use **cmd.exe** and not powershell or any other shell, the instructions may not work otherwise.

### Download Sources

Clone the repository.
```shell
git clone https://github.com/emomaxd/zenith.git
```

### Compile Zenith

Create build directory
```shell
mkdir build && cd build
```

Configure with CMake
```shell
cmake ..
```

Compile using CMake, Then in the following command just substitute [CONFIG] with one of the following options: Release, Debug, RelWithDebInfo
```shell
cmake --build . --target INSTALL --config [CONFIG]
```

## Building Zenith on Linux

### Prerequisites

- CMake
- Git
- Clang (or another CXX compiler)
- Ninja (or another generator)

### Download Sources

Clone the repository.
```shell
git clone https://github.com/emomaxd/zenith.git
```

### Compile Zenith

Create build directory
```shell
mkdir build && cd build
```

Configure with CMake
```shell
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G ninja ..
or
cmake ..
```

Compile using CMake, Then in the following command just substitute [CONFIG] with one of the following options: Release, Debug.
```shell
cmake --build . --target INSTALL --config [CONFIG]
```

---

## Building Zenith on macOS

**macOS is not supported yet.**  
Support for macOS is planned for future releases. If you're interested in helping out or testing, feel free to contribute to the development or check back later for updates.

Alternatively, you may follow the instructions for Linux as a workaround if you want to try building on macOS with some adjustments.

NOTE: macOS support would really take **some** time.
