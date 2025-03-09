# ============================
# CMake Version and Initial Setup
# ============================
cmake_minimum_required(VERSION 3.10)

# Prevent in-source builds (stay out of the source directory)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} AND NOT DEFINED WITH_IN_SOURCE_BUILD)
  message(FATAL_ERROR
    "CMake generation for Zenith is not allowed within the source directory!"
    "\nRemove the CMakeCache.txt and CMakeFiles directories and build out-of-source."
    "\nExample:"
    "\n mkdir build && cd build && cmake .."
  )
endif()

# ============================
# Project Initialization
# ============================
project(zenith)

# Enable testing
enable_testing()

# Set default CMake build type if not defined
if(NOT DEFINED CMAKE_BUILD_TYPE_INIT)
  set(CMAKE_BUILD_TYPE_INIT "Release")
endif()
mark_as_advanced(CMAKE_BUILD_TYPE_INIT)

# Set compile definitions based on the build configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
  $<$<CONFIG:Debug>:ZENITH_DEBUG>
)

# -----------------------------------------------------------------------------
# Set Platform-Specific Defines
# -----------------------------------------------------------------------------
if(WIN32)
  add_definitions(-DZENITH_PLATFORM_WINDOWS)
elseif(APPLE)
  add_definitions(-DZENITH_PLATFORM_MACOS)
elseif(UNIX)
  add_definitions(-DZENITH_PLATFORM_LINUX)
endif()

# -----------------------------------------------------------------------------
# Export Compile Commands (for VSCode, etc.)
# -----------------------------------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
# -----------------------------------------------------------------------------

# -----------------------------------------------------------------------------
# Set up Installation Directories
# -----------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Set output directories for library and executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # Static libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # Shared libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # Executables

add_subdirectory(source)
add_subdirectory(test)
add_subdirectory(tools)

# ============================
# End of CMake Configuration
# ============================
