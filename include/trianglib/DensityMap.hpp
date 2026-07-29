//
// Created by jassoka on 7/13/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_DENSITYMAP_H
#define DELENAUYTESSELATIONGENERATION_DENSITYMAP_H
#include <random>

#include "ImageFile.hpp"

class ImageFile;

namespace trianglib
{
    /**
     * @brief DensityMap is a class for generating probability distribution
     * from discrete maps
     */
    class DensityMap
    {
    public:
        /** @brief Generates distribution from an image file */
        explicit DensityMap(const ImageFile &file);
        /** @brief Samples a random coordinate from the current distribution */
        template <typename vectorType>
        vectorType sampleRandomCoordinate();
        /** @brief Samples n random coordinates to a list of vectors */
        template <typename vectorType>
        std::vector<vectorType> sampleNRandomCoordinates(int n);
    private:
        void generateDistribution(const ImageFile &file);
        /** @brief Pointer to 0.0 to 1.0 values for image cumulative distribution */
        std::vector<float>mDistribution;
        int mDistributionWidth;
        int mDistributionHeight;
        std::mt19937 mGen;
    };
}

#include "impl/DensityMap.inl"

#endif //DELENAUYTESSELATIONGENERATION_DENSITYMAP_H
