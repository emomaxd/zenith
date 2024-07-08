project(Examples)

file(GLOB_RECURSE EXAMPLES_SOURCES
    "${CMAKE_SOURCE_DIR}/Examples/*.cpp"
    "${CMAKE_SOURCE_DIR}/Examples/*.hpp"
    "${CMAKE_SOURCE_DIR}/Examples/*.h"
)

add_executable(Examples ${EXAMPLES_SOURCES})

target_link_libraries(Examples PRIVATE 
    Compiler
)

target_include_directories(Examples PRIVATE
    "${CMAKE_SOURCE_DIR}/Compiler/src"
)