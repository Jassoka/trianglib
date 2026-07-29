
#include <iostream>

#include "../include/trianglib/DensityMap.h"
#include "../include/trianglib/SVGFile.h"
#include "../include/trianglib/Triangulation.h"
#include "../include/trianglib/Mesh.h"
#include <chrono>
#include <filesystem>


#ifndef PROJECT_ROOT_DIR
    #define PROJECT_ROOT_DIR "."
#endif

int main()
{
    std::filesystem::path rootDir = PROJECT_ROOT_DIR;
    std::filesystem::path inputPath = rootDir / "examples" / "assets" / "france_population_map.png";
    const auto file = trianglib::ImageFile(inputPath.string(), trianglib::GREYSCALE);
    if (!file.isOpen())
    {
        std::cerr << "Failed to open input file " << inputPath << '\n';
    }

    auto map = trianglib::DensityMap(file);

    std::filesystem::path outputPath = rootDir / "output" / "france_output.svg";
    auto svgFile = trianglib::SVGFile(outputPath.string());
    if (!svgFile.isOpen())
    {
        std::cerr << "Failed to open output file " << outputPath << '\n';
    }
    trianglib::Mesh2D mesh;
    for (int i = 0; i < 1000; i++)
    {
        mesh.pushVertex(map.sampleRandomCoordinate());
    }
    auto start = std::chrono::high_resolution_clock::now();
    trianglib::Triangulation2D::triangulate(mesh);
    auto end = std::chrono::high_resolution_clock::now();

    // 3. Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Triangulation took " << duration.count() << " ms.\n";
    svgFile.writeMesh(mesh);
    svgFile.close();
    return 0;
}
