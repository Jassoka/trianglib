//
// Created by jassoka on 7/14/26.
//

#include "trianglib/Mesh.h"
#include <Eigen/Dense>

#include "geometryUtils.hpp"
#include "trianglib/types.hpp"

template class trianglib::Mesh<trianglib::vec2>;

template <typename EigenVectorType>
uint32_t trianglib::Mesh<EigenVectorType>::pushVertex(const vecType& v)
{
    mVertices.push_back(v);
    return mVertices.size() - 1;
}


template <typename EigenVectorType>
uint64_t trianglib::Mesh<EigenVectorType>::edgeMapKey(const uint32_t origin, const uint32_t end)
{
    return detail::hashEdge(origin, end);
}

template <typename EigenVectorType>
int32_t trianglib::Mesh<EigenVectorType>::getEdge(const uint32_t origin, const uint32_t end)
{
    const auto it = mEdgeMap.find(edgeMapKey(origin, end));
    if (it == mEdgeMap.end()) return -1;
    return it->second;
}

template <typename EigenVectorType>
uint32_t trianglib::Mesh<EigenVectorType>::addEdge(const uint32_t origin, const uint32_t end)
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

template <typename EigenVectorType>
uint32_t trianglib::Mesh<EigenVectorType>::addEdge(const Edge e)
{
    return addEdge(e[0], e[1]);
}
