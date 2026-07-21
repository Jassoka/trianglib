//
// Created by jassoka on 7/16/26.
//

#ifndef DELENAUYTESSELATIONGENERATION_FILE_H
#define DELENAUYTESSELATIONGENERATION_FILE_H

namespace trianglib
{
    /**
     * Class for opening and editing files
     */
    class File
    {
    public:
        /** @brief Returns false if file failed to open */
        [[nodiscard]] virtual bool isOpen() const = 0;
        /** @brief Closes file */
        virtual void close() = 0;
    };
}
#endif //DELENAUYTESSELATIONGENERATION_FILE_H
