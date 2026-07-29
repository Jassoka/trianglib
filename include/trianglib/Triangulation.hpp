//
// Created by jassoka on 7/15/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_TRIANGULATION_H
#define DELENAUYTESSELATIONGENERATION_TRIANGULATION_H
#include "trianglib/Mesh.hpp"

namespace trianglib
{
    class Triangulation2D
    {
    public:
        template <typename vectorType2D>
        [[nodiscard]] static Mesh<vectorType2D> triangulate(const std::vector<vectorType2D> &points);
    private:
        /**
         * @param points Reference to vector of vertices
         * @param pointIndices Indices of the vertices considered in the triangulation
         * If empty, all vertices are considered
         * @return Vector of triangles containing indices
         */
        template <typename vectorType2D>
        static std::vector<Triangle> triangulateImpl(const std::vector<vectorType2D> &points,
            const std::vector<uint32_t> &pointIndices = std::vector<uint32_t>());

        template <typename vectorType2D>
        static void addTriangle(Mesh<vectorType2D> &mesh, Triangle t);

        /** Returns whether the vertex D is in the circumcircle for the triangle ABC */
        template <typename vectorType2D>
        static bool isInCircumcircle2D(vectorType2D A, vectorType2D B, vectorType2D C, vectorType2D D);

        // Boucle de triangulation
        static Edge getTriangleEdge(const Triangle &t, const int edgeIdx)
        {
            return Edge{t[edgeIdx], t[(edgeIdx+1)%3]};
        }

    };
}

#include "impl/Triangulation.inl"
#endif //DELENAUYTESSELATIONGENERATION_TRIANGULATION_H
