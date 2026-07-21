cmake_minimum_required(VERSION 3.15)
project(DelenauyTesselationGeneration LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check if we are the top-level project, or nested inside another project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_TOP_LEVEL ON)
else()
    set(IS_TOP_LEVEL OFF)
endif()

# Default to ON if standing alone, default to OFF if used as a library
option(BUILD_EXAMPLES "Build example applications" ${IS_TOP_LEVEL})

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()