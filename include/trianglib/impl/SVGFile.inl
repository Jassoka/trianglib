//
// Created by jassoka on 7/13/26.
//

#include "trianglib/Mesh.hpp"

trianglib::SVGFile::SVGFile(const std::string& path, const uint32_t width, const uint32_t height):
    mFile(path),
    mWidth(width),
    mHeight(height)
{
    mOpened = mFile.is_open();
    if (mOpened)
        writeHeader();
}

trianglib::SVGFile::~SVGFile()
{
    close();
}

void trianglib::SVGFile::writeHeader()
{
    mFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" ";
    mFile << "width=\"" << mWidth << "\" height=\"" << mHeight << "\" ";
    mFile << "viewBox=\"0 0 " << mWidth << " " << mHeight << "\">\n";

    mFile << "  <rect width=\"100%\" height=\"100%\" fill=\"#111111\" />\n";
}

void trianglib::SVGFile::writeFooter()
{
    mFile << "</svg>\n";
}

bool trianglib::SVGFile::isOpen() const
{
    return mOpened;
}

void trianglib::SVGFile::close()
{
    if (isOpen())
    {
        writeFooter();
        mFile.close();
        mOpened = false;
    }
}

template <typename vectorType2D>
void trianglib::SVGFile::addPoint(const vectorType2D& point)
{
    mFile << "  <circle cx=\"" << util::nth<0, vectorType2D>(point)*mWidth
                << "\" cy=\"" << util::nth<1, vectorType2D>(point)*mHeight
                << "\" r=\"1.0\" fill=\"#ffffff\" opacity=\"0.8\" />\n";
}

template <typename vectorType2D>
void trianglib::SVGFile::addLine(const vectorType2D& origin, const vectorType2D& end)
{
    mFile << "<line x1=\"" << util::nth<0, vectorType2D>(origin) * mWidth
        << "\" y1=\"" << util::nth<1, vectorType2D>(origin) * mHeight
        << "\" x2=\"" << util::nth<0, vectorType2D>(end) * mWidth
        << "\" y2=\"" << util::nth<1, vectorType2D>(end) * mHeight
        << "\" stroke=\"#ffffff\" stroke-width=\"1\" />\n";
}

template <typename vectorType2D>
void trianglib::SVGFile::writeMesh(const Mesh<vectorType2D>& mesh)
{
    const auto points = mesh.getVertices();
    for (const auto p : points)
    {
        addPoint(p);
    }
    for (const auto [origin, end] : mesh.getEdges())
    {
        addLine(points[origin], points[end]);
    }
}

