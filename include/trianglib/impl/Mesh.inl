//
// Created by jassoka on 7/14/26.
//

#include "geometryUtils.hpp"

namespace trianglib
{

    template <typename vectorType>
    Mesh<vectorType>::Mesh(const std::vector<vectorType>& vertices)
    {
        mVertices = vertices;
    }

    template <typename vectorType2D>
    uint32_t Mesh<vectorType2D>::pushVertex(const vectorType2D& v)
    {
        mVertices.push_back(v);
        return mVertices.size() - 1;
    }


    template <typename vectorType2D>
    uint64_t Mesh<vectorType2D>::edgeMapKey(const uint32_t origin, const uint32_t end)
    {
        return detail::hashEdge(origin, end);
    }

    template <typename vectorType2D>
    int32_t Mesh<vectorType2D>::getEdge(const uint32_t origin, const uint32_t end)
    {
        const auto it = mEdgeMap.find(edgeMapKey(origin, end));
        if (it == mEdgeMap.end()) return -1;
        return it->second;
    }

    template <typename vectorType2D>
    uint32_t Mesh<vectorType2D>::addEdge(const uint32_t origin, const uint32_t end)
    {
        int32_t edgeIdx = getEdge(origin, end);
        if (edgeIdx == -1)
        {
            edgeIdx = mEdges.size();
            mEdgeMap.insert(std::make_pair(edgeMapKey(origin, end), mEdges.size()));
            mEdges.push_back(Edge{origin, end});
        }
        return edgeIdx;
    }

    template <typename vectorType2D>
    uint32_t Mesh<vectorType2D>::addEdge(const Edge e)
    {
        return addEdge(e[0], e[1]);
    }
}
