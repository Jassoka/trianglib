//
// Created by jassoka on 7/15/26.
//

#include "trianglib/Triangulation.h"
#include "trianglib/Mesh.h"
#include <unordered_set>
#include "geometryUtils.hpp"

void trianglib::Triangulation2D::addTriangle(Mesh2D &mesh,  const Triangle t)
{
    for (int i = 0; i < 3; i++)
        mesh.addEdge(getTriangleEdge(t, i));
}

// For predicates.c
extern "C" {
    void exactinit();
    double incircle(double* pa, double* pb, double* pc, double* pd);
}

bool trianglib::Triangulation2D::isInCircumcircle2D(vec2 A, vec2 B, vec2 C, vec2 D)
{
    double pa[2] = { static_cast<double>(A.x()), static_cast<double>(A.y()) };
    double pb[2] = { static_cast<double>(B.x()), static_cast<double>(B.y()) };
    double pc[2] = { static_cast<double>(C.x()), static_cast<double>(C.y()) };
    double pd[2] = { static_cast<double>(D.x()), static_cast<double>(D.y()) };

    const double circleTest = incircle(pa, pb, pc, pd);
    return circleTest > 0.0;
}

void trianglib::Triangulation2D::triangulate(Mesh2D &mesh)
{
    const auto triangulation = triangulateImpl(mesh.getVertices());
    for (const auto &t: triangulation)
    {
        addTriangle(mesh, t);
    }
}


std::vector<trianglib::Triangle> trianglib::Triangulation2D::triangulateImpl(const std::vector<vec2> &points,
                                                                             const std::vector<uint32_t> &pointIndices)
{
    exactinit();

    // giga triangle
    float minX, maxX, minY, maxY;
    if (points.size() > 0)
    {
        auto v = points[0];
        minX = v.x(); maxX = v.x(); minY = v.y(); maxY = v.y();
    }
    for (auto v: points)
    {
        if (v.x() < minX) minX = v.x();
        if (v.x() > maxX) maxX = v.x();
        if (v.y() < minY) minY = v.y();
        if (v.y() > maxY) maxY = v.y();
    }
    const float d = 2*std::max(maxX - minX, maxY - minY);
    // Center
    const float Cx = (maxX+minX)/2; const float Cy = (maxY+minY)/2;


    const std::array<vec2, 3> initialTriangle = {
        vec2(Cx - 2*d, Cy - d),
        vec2(Cx + 2*d, Cy - d),
        vec2(Cx, Cy + 2*d)
    };

    std::vector triangulation = {Triangle{
        static_cast<uint32_t>(points.size()),
        static_cast<uint32_t>(points.size()+1),
        static_cast<uint32_t>(points.size()+2)
    }
    };

    std::vector<vec2> extendedPoints;
    extendedPoints.reserve(points.size() + initialTriangle.size());
    extendedPoints.insert(extendedPoints.end(), points.begin(), points.end());
    extendedPoints.insert(extendedPoints.end(), initialTriangle.begin(), initialTriangle.end());

    auto processVertex = [&triangulation, &extendedPoints](const uint32_t vertexIndex)
    {
        std::vector<Triangle> badTriangles;
        for (auto it = triangulation.begin(); it != triangulation.end();)
        {
            if (Triangle t = *it;
                isInCircumcircle2D(extendedPoints[t[0]], extendedPoints[t[1]], extendedPoints[t[2]], extendedPoints[vertexIndex]))
            {
                badTriangles.push_back(*it);
                it = triangulation.erase(it);
            }
            else { ++it; }
        }
        // for each triangle in badtriangles
        std::list<Edge> polygon; // polygon is a list of edges
        std::unordered_map<uint64_t, std::list<Edge>::iterator> visitedEdges;
        for (int triangleIdx = 0; triangleIdx < badTriangles.size(); triangleIdx++)
        {
            Triangle triangle = badTriangles[triangleIdx];
            for (int localEdgeIdx = 0; localEdgeIdx < 3; localEdgeIdx++)
            {
                const auto currentEdge = getTriangleEdge(triangle, localEdgeIdx);
                const auto currentEdgeHash = detail::hashEdge(currentEdge);
                // If edge hasn't been found, add it to polygon
                if (auto edgeIt = visitedEdges.find(currentEdgeHash);
                    edgeIt == visitedEdges.end())
                {
                    polygon.push_back(currentEdge);
                    auto newEdgeIt = std::prev(polygon.end());
                    visitedEdges.insert(std::make_pair(currentEdgeHash, newEdgeIt));
                } // Else, it's a shared edge, remove it
                else
                {
                    polygon.erase(edgeIt->second);
                    visitedEdges.erase(edgeIt);
                }
            }
        }
        for (const auto edge : polygon)
        {
            const Triangle t = {
                edge[0],
                edge[1],
                vertexIndex
            };
            triangulation.push_back(t);
        }
    };

    // Case where all indices are considered
    if (pointIndices.size() == 0)
        for (uint32_t pointIdx = 0; pointIdx < points.size(); pointIdx++) { processVertex(pointIdx); }
    else
    {
        for (const auto pointIdx : pointIndices) { processVertex(pointIdx); }
    }
    // Remove each triangle with vertices from the original triangulation
    for (auto it = triangulation.begin(); it != triangulation.end();)
    {
        bool sharesEdgeWithInitialTriangle = false;
        for (int i = 0; i < 3; i++)
        {
            if ((*it)[i] == points.size() ||
                (*it)[i] == points.size()+1 ||
                (*it)[i] == points.size()+2)
            {
                sharesEdgeWithInitialTriangle = true;
            }
        }
        if (sharesEdgeWithInitialTriangle) it = triangulation.erase(it);
        else ++it;
    }
    return triangulation;
}