//
// Created by jassoka on 7/13/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_SVGWRITER_H
#define DELENAUYTESSELATIONGENERATION_SVGWRITER_H
#include <cstdint>
#include <fstream>

#include "File.hpp"
#include "Mesh.hpp"


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

        template <typename vectorType2D>
        void writeMesh(const Mesh<vectorType2D>& mesh);
        template <typename vectorType2D>
        void addPoint(const vectorType2D &point);
        template <typename vectorType2D>
        void addLine(const vectorType2D &origin, const vectorType2D &end);

    private:
        void writeHeader();
        void writeFooter();

        std::ofstream mFile;
        bool mOpened;
        uint32_t mWidth;
        uint32_t mHeight;
    };
}

#include "impl/SVGFile.inl"
#endif //DELENAUYTESSELATIONGENERATION_SVGWRITER_H
