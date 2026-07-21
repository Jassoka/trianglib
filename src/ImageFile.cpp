//
// Created by jassoka on 7/13/26.
//

#include "../include/trianglib/ImageFile.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef ENABLE_DEBUG
std::ostream& operator<<(std::ostream& os, const trianglib::Pixel p)
{
    os << static_cast<int>(p.r) << " "
        << static_cast<int>(p.g) << " "
        << static_cast<int>(p.b) << " "
        << static_cast<int>(p.a) << '\n';
    return os;
}
#endif

trianglib::ImageFile::ImageFile(const std::string& path, const ChannelType imageType)
{
    const int desiredChannels = imageType;
    mData = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, desiredChannels);
    if (desiredChannels != 0)
    {
        // Cas ou on a choisit notre nombre de canaux
        mChannels = desiredChannels;
    }
    mChannelType = static_cast<ChannelType>(mChannels);
    // Failed import
    if (mData != nullptr)
        mOpened = true;
}

trianglib::ImageFile::~ImageFile()
{
    ImageFile::close();
}

void trianglib::ImageFile::close()
{
    stbi_image_free(mData);
}

bool trianglib::ImageFile::isOpen() const
{
    return mOpened;
}

trianglib::Pixel trianglib::ImageFile::operator[](const int i) const
{
    const unsigned char *pixelPtr = &mData[i*mChannels];
    switch (mChannelType)
    {
    case RGB:
        return Pixel{.r = pixelPtr[0], .g = pixelPtr[1], .b = pixelPtr[2], .a = 255};
    case RGBA:
        return Pixel{.r = pixelPtr[0], .g = pixelPtr[1], .b = pixelPtr[2], .a = pixelPtr[3]};
    case GREYSCALE:
        return Pixel{.r = pixelPtr[0], .g = pixelPtr[0], .b = pixelPtr[0], .a = 255};
    default:
        return Pixel{.r = 0, .g = 0, .b = 0, .a = 0};
    }
}




