# About Zenith
Zenith is a minimal C compiler front-end capable of generating LLVM IR. It is not intended to be a full-fledged compiler but rather a learning project for exploring compilers and LLVM.

## Architecture
Zenith follows a modular architecture, ensuring ease of extension and modification. The source code resides in the source/ directory and is built as a library, while headers are available in include/. The tools/driver project provides a CLI for terminal usage. Testing is in test/, though the framework is not fully set up yet.

Project documentation is stored in doc/, with plans for a documentation generator in the future. Clang is the preferred compiler for maintainers. Code style is enforced through .clang-format and .clang-tidy, which should be used as needed.

Development is ongoing, and contributions are welcome. Check out our [contribution guidelines](../../CONTRIBUTING.md) to get involved!
