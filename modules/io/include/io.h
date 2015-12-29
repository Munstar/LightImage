#ifndef LIGHTIMAGE_IO_H
#define LIGHTIMAGE_IO_H

#include <QtCore/qstring.h>
#include "../../core/include/types.h"
#include "../../core/include/core.hpp"

namespace li {
#pragma pack(2)
    typedef struct _BITMAPFILEHEADER {
        LI_U8 Type[2];
        LI_U32 FileSize;
        LI_U16 Reserved1;
        LI_U16 Reserved2;
        LI_U32 Offset;
    } BitMapFileHeader;
#pragma pack()

#pragma pack(2)
    typedef struct _BITMAPINFOHEADER {
        LI_U32 InfoSize;
        LI_U32 Width;
        LI_U32 Height;
        LI_U16 Planes;
        LI_U16 BitCount;
        LI_U32 Compression;
        LI_U32 ImageSize;
        LI_U32 HResolution;
        LI_U32 VResolution;
        LI_U32 ColorCount;
        LI_U32 ColorImportant;
    } BitMapInfoHeader;
#pragma pack()

    Image imload(const char *fname);

    bool imsave(Image &_im, const char *fname);
}


#endif //LIGHTIMAGE_IO_H
