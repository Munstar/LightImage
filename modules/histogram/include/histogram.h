//
// Created by xin on 11/17/15.
//

#ifndef LIGHTIMAGE_HISTOGRAM_H
#define LIGHTIMAGE_HISTOGRAM_H

#include "../../core/include/core.hpp"

namespace li {
    class Histogram {
    public:

        Histogram();

        Histogram(Image &_im);

        ~Histogram();

        Image Render(int _width, int _height);

        int channles;
        int *data;

    };

    Image histogram_balance(Image &_im);

}
#endif //LIGHTIMAGE_HISTOGRAM_H
