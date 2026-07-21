//
// Created by jassoka on 7/14/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_MESH_H
#define DELENAUYTESSELATIONGENERATION_MESH_H
#include <cstdint>
#include <vector>
#include <unordered_map>
#include "types.hpp"


namespace trianglib
{

    template<typename EigenVectorType>
    class Mesh
    {
        using vecType = EigenVectorType;
        using scalar = typename vecType::Scalar;
    public:
        /** @return Const reference to mesh's vertex array */
        const std::vector<vecType>& getVertices() const { return mVertices; }
        /** @return Const reference to mesh's edge array */
        const std::vector<Edge>& getEdges() const { return mEdges; }

        /** Pushes a vertex to the mesh
         * @return Vertex index
         */
        uint32_t pushVertex(const vecType& v);

        /**
         * Returns edge index which spans from origin to end
         * Returns -1 if non existent
         */
        int32_t getEdge(uint32_t origin, uint32_t end);

        /**
         * Adds an edge to the mesh
         * Checks for existence, returns edge index
         */
        uint32_t addEdge(uint32_t origin, uint32_t end);
        uint32_t addEdge(Edge e);

    private:
        static uint64_t edgeMapKey(uint32_t origin, uint32_t end);
        std::vector<vecType> mVertices;
        std::vector<Face> mFaces;
        std::vector<Edge> mEdges;
        /** Takes an "key" for two vertices, and returns the edge index if it exists */
        std::unordered_map<uint64_t, uint32_t> mEdgeMap;

        static constexpr int mDimension = EigenVectorType::SizeAtCompileTime;
    };
}
#endif //DELENAUYTESSELATIONGENERATION_MESH_H
