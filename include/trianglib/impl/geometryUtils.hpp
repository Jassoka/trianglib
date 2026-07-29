//
// Created by jassoka on 7/16/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_GEOMETRYUTILS_H
#define DELENAUYTESSELATIONGENERATION_GEOMETRYUTILS_H
#include <algorithm>
#include <cstdint>

namespace trianglib::detail {
    /** Utility function for hashing edge values */
    inline uint64_t hashEdge(const uint32_t origin, const uint32_t end) {
        const uint32_t low  = std::min(origin, end);
        const uint32_t high = std::max(origin, end);
        return (static_cast<uint64_t>(high) << 32) | low;
    }

    inline uint64_t hashEdge(const Edge e) {
        return hashEdge(e[0], e[1]);
    }
}
#endif //DELENAUYTESSELATIONGENERATION_GEOMETRYUTILS_H
