//
// Created by xin on 11/10/15.
//

#ifndef LIGHTIMAGE_IMAGE_H
#define LIGHTIMAGE_IMAGE_H

#include "matrix.hpp"
#include "types.h"

namespace li {
    typedef Matrix_<LI_U8> Image;
}

/*

namespace li
{
    enum Format{Invalid, GrayScale, RGB888, RGBA8888};

    class Image : public Matrix_<LI_U8>
    {
    public:

        Image();
        Image(Image& _im);
        Image(int _width, int _height, Format _format);
        Image(int _width, int _height, Format _format, LI_U8* _data);
        Image(int _width, int _height, Format _format, LI_U8 _value);

        Format format;

    };
}

 */

#endif //LIGHTIMAGE_IMAGE_H
