//
// Created by xin on 12/19/15.
//

#ifndef LIGHTIMAGE_DCT_H
#define LIGHTIMAGE_DCT_H

#include "LightImage.h"

namespace li {
    Matrix_<float> dct(Image &_im);

    Image idct(Matrix_<float> &_ct, int width, int height);

    Image renderPowerSpectrum(Matrix_<float> &ft);
}

#endif //LIGHTIMAGE_DCT_H
