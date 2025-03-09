set(CMAKE_CXX_STANDARD 17)

set(INC
  ../../include/
)

set(LIB
  lexer
  parser
)

set(SRC
  main.cpp
)

add_executable(driver ${SRC})

target_include_directories(driver PUBLIC ${INC})

target_link_libraries(driver PRIVATE ${LIB})
