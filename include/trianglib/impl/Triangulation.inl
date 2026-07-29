//
// Created by jassoka on 7/15/26.
//
#include <list>

#include "trianglib/Mesh.hpp"
#include "geometryUtils.hpp"

// For predicates.c
extern "C" {
void exactinit();
double incircle(double* pa, double* pb, double* pc, double* pd);
}

namespace trianglib
{
    template <typename vectorType2D>
    void Triangulation2D::addTriangle(Mesh<vectorType2D> &mesh,  const Triangle t)
    {
        for (int i = 0; i < 3; i++)
            mesh.addEdge(getTriangleEdge(t, i));
    }

    // Functions pour accès facile à x et y
    template<typename vectorType2D>
    auto x = [](vectorType2D v)
    { return util::nth<0, vectorType2D>(v); };

    template<typename vectorType2D>
    auto y = [](vectorType2D v)
    { return util::nth<1, vectorType2D>(v); };

    template <typename vectorType2D>
    bool Triangulation2D::isInCircumcircle2D(vectorType2D A, vectorType2D B, vectorType2D C, vectorType2D D)
    {
        double pa[2] = { static_cast<double>(x<vectorType2D>(A)), static_cast<double>(y<vectorType2D>(A)) };
        double pb[2] = { static_cast<double>(x<vectorType2D>(B)), static_cast<double>(y<vectorType2D>(B)) };
        double pc[2] = { static_cast<double>(x<vectorType2D>(C)), static_cast<double>(y<vectorType2D>(C)) };
        double pd[2] = { static_cast<double>(x<vectorType2D>(D)), static_cast<double>(y<vectorType2D>(D)) };

        const double circleTest = incircle(pa, pb, pc, pd);
        return circleTest > 0.0;
    }

    template <typename vectorType2D>
    Mesh<vectorType2D> Triangulation2D::triangulate(const std::vector<vectorType2D> &points)
    {
        auto mesh = Mesh<vectorType2D>(points);
        const auto triangulation = triangulateImpl(points);
        for (const auto &t: triangulation)
        {
            Triangulation2D::addTriangle<vectorType2D>(mesh, t);
        }
        return mesh;
    }

    template<typename vectorType2D>
    vectorType2D make_point(const util::get_scalar_type<vectorType2D> x, const util::get_scalar_type<vectorType2D> y)
    {
        vectorType2D point;
        util::set_nth<0, vectorType2D>(point, x);
        util::set_nth<1, vectorType2D>(point, y);
        return point;
    }


    template <typename vectorType2D>
    std::vector<Triangle> Triangulation2D::triangulateImpl(const std::vector<vectorType2D> &points,
                                                                                 const std::vector<uint32_t> &pointIndices)
    {   using scalar = util::get_scalar_type<vectorType2D>;

        // giga triangle
        scalar minX, maxX, minY, maxY;
        if (points.size() > 0)
        {
            auto v = points[0];
            minX = x<vectorType2D>(v); maxX = x<vectorType2D>(v); minY = y<vectorType2D>(v); maxY = y<vectorType2D>(v);
        }
        for (auto v: points)
        {
            if (x<vectorType2D>(v) < minX) minX = x<vectorType2D>(v);
            if (x<vectorType2D>(v) > maxX) maxX = x<vectorType2D>(v);
            if (y<vectorType2D>(v) < minY) minY = y<vectorType2D>(v);
            if (y<vectorType2D>(v) > maxY) maxY = y<vectorType2D>(v);
        }
        const scalar d = 2*std::max(maxX - minX, maxY - minY);
        // Center
        const scalar Cx = (maxX+minX)/2; const scalar Cy = (maxY+minY)/2;


        const std::array<vectorType2D, 3> initialTriangle = {
            make_point<vectorType2D>(Cx - 2*d, Cy - d),
            make_point<vectorType2D>(Cx + 2*d, Cy - d),
            make_point<vectorType2D>(Cx, Cy + 2*d)
        };

        std::vector triangulation = {Triangle{
            static_cast<uint32_t>(points.size()),
            static_cast<uint32_t>(points.size()+1),
            static_cast<uint32_t>(points.size()+2)
        }
        };

        std::vector<vectorType2D> extendedPoints;
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
}