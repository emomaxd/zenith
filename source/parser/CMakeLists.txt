set(CMAKE_CXX_STANDARD 17)

set(INC
  ../../include
)

set(LIB
)

set(SRC
  parser.cpp
)

add_library(parser ${SRC})

target_include_directories(parser PUBLIC ${INC})

target_link_libraries(parser PRIVATE ${LIB})
