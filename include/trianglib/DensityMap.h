//
// Created by jassoka on 7/13/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_DENSITYMAP_H
#define DELENAUYTESSELATIONGENERATION_DENSITYMAP_H
#include <random>
#include <Eigen/Core>

#include "ImageFile.h"

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
        /**
         * Generates distribution from an image file
         */
        explicit DensityMap(const ImageFile &file);
        /**
         * Samples a random coordinate from the current distribution
         */
        Eigen::Vector2f sampleRandomCoordinate();
    private:
        void generateDistribution(const ImageFile &file);
        /** @brief Pointer to 0.0 to 1.0 values for image cumulative distribution */
        std::vector<float>mDistribution;
        int mDistributionWidth;
        int mDistributionHeight;
        std::mt19937 mGen;
    };
}


#endif //DELENAUYTESSELATIONGENERATION_DENSITYMAP_H
