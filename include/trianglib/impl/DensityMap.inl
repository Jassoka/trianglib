//
// Created by jassoka on 7/13/26.
//

#include "trianglib/ImageFile.hpp"
#include "trianglib/types.hpp"

trianglib::DensityMap::DensityMap(const ImageFile& file):
    mDistributionWidth(file.width()),
    mDistributionHeight(file.height()),
    mGen(std::random_device{}())
{
    generateDistribution(file);
}


void trianglib::DensityMap::generateDistribution(const ImageFile &file)
{
    const int totalSize = mDistributionHeight*mDistributionWidth;
    mDistribution.resize(totalSize);


    mDistribution[0] = file[0].getIntensity();
    for (int i = 1; i < totalSize; i++)
        mDistribution[i] = mDistribution[i-1] + file[i].getIntensity();

    /* Normalising data */
    for (int i = 0; i < totalSize; i++)
        mDistribution[i] /= mDistribution[totalSize-1];
}


template <typename vectorType>
vectorType trianglib::DensityMap::sampleRandomCoordinate()
{

    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    const float roll = dis(mGen);

    int low = 0;
    int high = mDistribution.size() - 1;
    int index = high;

    while (low <= high) {
        if (const int mid = low + (high - low) / 2;
            mDistribution[mid] >= roll) {
            index = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    const float x = static_cast<float>(index % mDistributionWidth) / static_cast<float>(mDistributionWidth);
    const float y = static_cast<float>(index / mDistributionWidth) / static_cast<float>(mDistributionHeight);
    vectorType vec;
    util::set_nth<0, vectorType>(vec, x);
    util::set_nth<1, vectorType>(vec, y);
    return vec;
}

template <typename vectorType>
std::vector<vectorType> trianglib::DensityMap::sampleNRandomCoordinates(const int n)
{
    auto vec = std::vector<vectorType>();
    for (int i = 0; i < n; i++)
        vec.push_back(sampleRandomCoordinate<vectorType>());
    return vec;
}
