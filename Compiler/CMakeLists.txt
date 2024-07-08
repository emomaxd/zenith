project(Compiler)

file(GLOB_RECURSE COMPILER_SRC
    "${CMAKE_SOURCE_DIR}/Compiler/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Compiler/src/*.hpp"
    "${CMAKE_SOURCE_DIR}/Compiler/src/*.h"
)

add_library(Compiler 
    ${COMPILER_SRC}
)

target_include_directories(Compiler PRIVATE
    "${CMAKE_SOURCE_DIR}/Compiler/src"
)