//
// Created by jassoka on 7/13/26.
//

#include "trianglib/SVGFile.h"
#include "trianglib/Mesh.h"

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

void trianglib::SVGFile::addPoint(const Eigen::Vector2f& point)
{
    mFile << "  <circle cx=\"" << point[0]*mWidth
                << "\" cy=\"" << point[1]*mHeight
                << "\" r=\"1.0\" fill=\"#ffffff\" opacity=\"0.8\" />\n";
}

void trianglib::SVGFile::addLine(const Eigen::Vector2f& origin, const Eigen::Vector2f& end)
{
    mFile << "<line x1=\"" << origin.x()*mWidth << "\" y1=\"" << origin.y()*mHeight
        << "\" x2=\"" << end.x()*mWidth << "\" y2=\"" << end.y()*mHeight
        << "\" stroke=\"#ffffff\" stroke-width=\"1\" />\n";
}

void trianglib::SVGFile::writeMesh(const Mesh2D& mesh)
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

