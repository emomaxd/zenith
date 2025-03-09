set(CMAKE_CXX_STANDARD 17)

set(INC
  ../../include/
)

set(LIB
)

set(SRC
  lexer.cpp
)

add_library(lexer ${SRC})

target_include_directories(lexer PUBLIC ${INC})

target_link_libraries(lexer PRIVATE ${LIB})
