//
// Created by jassoka on 7/16/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_TYPES_H
#define DELENAUYTESSELATIONGENERATION_TYPES_H

#include <Eigen/Core>

namespace trianglib
{
    using vec2 = Eigen::Vector2f;
    using vec2i = Eigen::Vector2i;

    template <typename T>
    class Mesh;

    using Mesh2D = Mesh<vec2>;

    using Face = std::vector<uint32_t>;
    using Edge = std::array<uint32_t, 2>;
    using Triangle = std::array<uint32_t, 3>;
}

#endif //DELENAUYTESSELATIONGENERATION_TYPES_H
