cmake_minimum_required(VERSION 4.2)
project(DelenauyTesselationGeneration LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

# Mode debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(ENABLE_DEBUG)
endif()


# 1. Create the executable from your main.cpp
add_executable(france_triangulation FranceMapTriangulation.cpp)

# 2. Link it to the library built by the src folder
target_link_libraries(france_triangulation PRIVATE trianglib)

target_compile_definitions(france_triangulation PRIVATE
        PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
)
