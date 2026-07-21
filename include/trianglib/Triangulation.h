//
// Created by jassoka on 7/15/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_TRIANGULATION_H
#define DELENAUYTESSELATIONGENERATION_TRIANGULATION_H
#include "types.hpp"
#include "trianglib/Mesh.h"

namespace trianglib
{
    class Triangulation2D
    {
    public:
        static void triangulate(Mesh2D &mesh);
    private:
        /**
         * @param points Reference to vector of vertices
         * @param pointIndices Indices of the vertices considered in the triangulation
         * If empty, all vertices are considered
         * @return Vector of triangles containing indices
         */
        static std::vector<Triangle> triangulateImpl(const std::vector<vec2> &points,
            const std::vector<uint32_t> &pointIndices = std::vector<uint32_t>());
        static void addTriangle(Mesh2D &mesh, Triangle t);
        /** Returns whether the vertex D is in the circumcircle for the triangle ABC */
        static bool isInCircumcircle2D(vec2 A, vec2 B, vec2 C, vec2 D);

        // Boucle de triangulation
        static Edge getTriangleEdge(const Triangle &t, const int edgeIdx)
        {
            return Edge{t[edgeIdx], t[(edgeIdx+1)%3]};
        }

    };
}

#endif //DELENAUYTESSELATIONGENERATION_TRIANGULATION_H
