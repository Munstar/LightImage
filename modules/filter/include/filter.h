//
// Created by xin on 12/24/15.
//

#ifndef LIGHTIMAGE_FILTER_H
#define LIGHTIMAGE_FILTER_H

#include "LightImage.h"

namespace li {
    Image base_filter(Image &_im, Filter_kernel &kernel);

    Image smooth(Image &_im);

    Image sharp(Image &_im);

    Image median_filter(Image &_im);

    Image pepper_salt_noise(Image &_im, int cnt);
}

#endif //LIGHTIMAGE_FILTER_H
