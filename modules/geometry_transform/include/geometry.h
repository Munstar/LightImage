//
// Created by xin on 11/19/15.
//

#ifndef LIGHTIMAGE_GEOMETRY_H
#define LIGHTIMAGE_GEOMETRY_H

#include "LightImage.h"

namespace li {
    Image mirror(Image &_im, bool h, bool v);

    Image scale_nearest(Image &_im, int _width, int _height);

    Image scale_linear(Image &_im, int _width, int _height);

    Image rotate(Image &_im, double _angle);

    Image clip(Image &_im, int x1, int y1, int x2, int y2);

    Image move(Image &_im, int x, int y);

}
#endif //LIGHTIMAGE_GEOMETRY_H
