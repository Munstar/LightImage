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

    Image histogram_eq(Image &_im);

    double hist_simi(Image &_im1, Image &_im2);

}
#endif //LIGHTIMAGE_HISTOGRAM_H
