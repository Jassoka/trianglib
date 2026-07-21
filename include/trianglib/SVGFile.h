//
// Created by jassoka on 7/13/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_SVGWRITER_H
#define DELENAUYTESSELATIONGENERATION_SVGWRITER_H
#include <cstdint>
#include <fstream>

#include <Eigen/Core>

#include "File.h"
#include "types.hpp"


namespace trianglib
{
    constexpr uint32_t defaultSize = 1080;

    class SVGFile: public File
    {
    public:
        /** @brief Constructor for SVG File */
        explicit SVGFile(const std::string &path, uint32_t width = defaultSize, uint32_t height = defaultSize);
        ~SVGFile();
        void close() override;
        bool isOpen() const override;

        void writeMesh(const Mesh2D& mesh);
        void addPoint(const vec2 &point);
        void addLine(const vec2 &origin, const vec2 &end);

    private:
        void writeHeader();
        void writeFooter();

        std::ofstream mFile;
        bool mOpened;
        uint32_t mWidth;
        uint32_t mHeight;
    };
}

#endif //DELENAUYTESSELATIONGENERATION_SVGWRITER_H
