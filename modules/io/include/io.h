//
// Created by xin on 11/10/15.
//

#ifndef LIGHTIMAGE_IO_H
#define LIGHTIMAGE_IO_H

#include "../../core/include/types.h"
#include "../../core/include/matrix.hpp"

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
        LI_U32 RedMask;
        LI_U32 GreenMask;
        LI_U32 BlueMask;
        LI_U32 AlphaMask;
    } BitMapInfoHeader;
#pragma pack()

    Matrix_<LI_U8> imload(const char *fname);
}


#endif //LIGHTIMAGE_IO_H
