set(CMAKE_CXX_STANDARD 17)

set(INC
  ../../include
)

set(LIB
  lexer
  parser
)

set(SRC
  main.cpp
)

add_executable(initial_ast ${SRC})

target_include_directories(initial_ast PUBLIC ${INC})

target_link_libraries(initial_ast PRIVATE ${LIB})
