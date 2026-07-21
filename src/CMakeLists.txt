set_source_files_properties(predicates.c PROPERTIES LANGUAGE C)
set_source_files_properties(predicates.c PROPERTIES COMPILE_FLAGS "-std=gnu89")

add_library(trianglib STATIC
        ImageFile.cpp
        DensityMap.cpp
        SVGFile.cpp
        Mesh.cpp
        Triangulation.cpp
        geometryUtils.hpp
        predicates.c
)

include(FetchContent)

# Eigen

FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)


set(BUILD_TESTING OFF)
set(EIGEN_BUILD_TESTING OFF)
set(EIGEN_MPL2_ONLY ON)
set(EIGEN_BUILD_PKGCONFIG OFF)
set(EIGEN_BUILD_DOC OFF)
FetchContent_MakeAvailable(Eigen)

target_link_libraries(trianglib PUBLIC Eigen3::Eigen)

target_include_directories(trianglib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../libs
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_library(jassoka::trianglib ALIAS trianglib)