
#include <iostream>

#include "../include/trianglib/DensityMap.hpp"
#include "../include/trianglib/SVGFile.hpp"
#include "../include/trianglib/Triangulation.hpp"
#include "../include/trianglib/Mesh.hpp"
#include <chrono>
#include <filesystem>


#ifndef PROJECT_ROOT_DIR
    #define PROJECT_ROOT_DIR "."
#endif

using vec2 = std::array<float, 2>;

int main()
{
    const std::filesystem::path rootDir = PROJECT_ROOT_DIR;
    const std::filesystem::path inputPath = rootDir / "examples" / "assets" / "france_population_map.png";
    const auto file = trianglib::ImageFile(inputPath.string(), trianglib::GREYSCALE);
    if (!file.isOpen())
        std::cerr << "Failed to open input file " << inputPath << '\n';

    auto map = trianglib::DensityMap(file);

    const std::filesystem::path outputPath = rootDir / "output" / "france_output.svg";
    auto svgFile = trianglib::SVGFile(outputPath.string());
    if (!svgFile.isOpen())
        std::cerr << "Failed to open output file " << outputPath << '\n';


    auto pointCloud = map.sampleNRandomCoordinates<vec2>(2000);
    auto start = std::chrono::high_resolution_clock::now();
    auto mesh = trianglib::Triangulation2D::triangulate(pointCloud);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Triangulation took " << duration.count() << " ms.\n";
    svgFile.writeMesh(mesh);
    svgFile.close();
    return 0;

}