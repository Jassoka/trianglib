//
// Created by jassoka on 7/13/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_IMAGEFILE_H
#define DELENAUYTESSELATIONGENERATION_IMAGEFILE_H
#include <cstdint>
#include <random>
#include <string>

#include "File.h"

namespace trianglib
{
    /**
     * @brief Enum for image channel types
     */
    enum ChannelType
    {
        ANY = 0,
        GREYSCALE = 1,
        RGB = 3,
        RGBA = 4
    };

    struct Pixel
    {
        uint8_t r, g, b, a;

        /**
         * Returns pixel color intensity
         */
        [[nodiscard]] float getIntensity() const
        {
            return static_cast<float>(r)/(255.0*3) +
                    static_cast<float>(g)/(255.0*3) +
                    static_cast<float>(b)/(255.0*3);
        }
    };

    class ImageFile: public File
    {
    public:
        /**
         * Constructor for an image file
         * @param path File path
         * @param imageType Number of expected channel,
         * Use ANY (0) to use the image file's number of channels
         */
        explicit ImageFile(const std::string &path, ChannelType imageType = ANY);
        ~ImageFile();

        /** @copybrief File::close */
        void close() override;

        /** @copybrief File::isOpen */
        [[nodiscard]] bool isOpen() const override;
        /** @return Image width */
        int width() const {return mWidth;}
        /** @return Image height */
        int height() const {return mHeight;}
        /** Returns a copy of the i-th pixel (read as a 1D array) */
        Pixel operator[](int i) const;

    private:
        unsigned char *mData;
        int mWidth{};
        int mHeight{};
        int mChannels;

        bool mOpened = false;
        ChannelType mChannelType;
    };
}
#endif //DELENAUYTESSELATIONGENERATION_IMAGEFILE_H
