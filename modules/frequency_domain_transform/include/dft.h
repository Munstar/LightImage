#ifndef LIGHTIMAGE_DFT_H
#define LIGHTIMAGE_DFT_H

#include <complex>
#include "LightImage.h"

namespace li {
    Matrix_<complex<float>> dft(Image &_im);

    Image idft(Matrix_<complex<float>> &_im, int width, int height);

    Image renderPowerSpectrum(Matrix_<complex<float>> &ft);

    Image butterworth_filter(Image &_im, double d0, int level);

    void fft(complex<float> *dat, int n, bool inverse);
}

#endif //LIGHTIMAGE_DFT_H
