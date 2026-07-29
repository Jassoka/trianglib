cmake_minimum_required(VERSION 3.15)
project(trianglib LANGUAGES CXX C)

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

add_library(shewchuk_predicates STATIC libs/shewchuk/predicates.c
        libs/stb/stb_image.cpp)


if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(shewchuk_predicates PRIVATE -O3)
elseif(MSVC)
    target_compile_options(shewchuk_predicates PRIVATE /O2)
endif()

add_library(stb STATIC libs/stb/stb_image.h
        libs/stb/stb_image.cpp)
target_include_directories(stb PUBLIC libs)

add_library(trianglib INTERFACE)

target_include_directories(trianglib INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_sources(trianglib INTERFACE
        include/trianglib/DensityMap.hpp
        include/trianglib/File.hpp
        include/trianglib/ImageFile.hpp
        include/trianglib/Mesh.hpp
        include/trianglib/SVGFile.hpp
        include/trianglib/Triangulation.hpp
        include/trianglib/types.hpp
        include/trianglib/vectorTypes.hpp
        include/trianglib/impl/ImageFile.inl
        include/trianglib/impl/DensityMap.inl
        include/trianglib/impl/SVGFile.inl
        include/trianglib/impl/Triangulation.inl
        include/trianglib/impl/geometryUtils.hpp
        include/trianglib/vectorTypes.hpp
)

target_link_libraries(trianglib INTERFACE shewchuk_predicates)
target_link_libraries(trianglib INTERFACE stb)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()