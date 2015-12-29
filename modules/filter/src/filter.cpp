#include "../include/filter.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

namespace li {
    Image smooth(Image &_im) {
        Filter_kernel k(1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                        1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                        1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0);
        return base_filter(_im, k);
    }

    Image sharp(Image &_im) {
        Filter_kernel k(-1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0,
                        -1.0 / 9.0, 17.0 / 9.0, -1.0 / 9.0,
                        -1.0 / 9.0, -1.0 / 9.0, -1.0 / 9.0);
        return base_filter(_im, k);
    }

    Image median_filter(Image &_im) {
        LI_U8 *dat = new LI_U8[_im.width * _im.height];
        std::vector<unsigned char> kernel;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    for (int l = 0; l < 3; ++l) {
                        int m = i + k - 1;
                        int n = j + l - 1;
                        if (m < 0)
                            m = -m - 1;
                        if (n < 0)
                            n = -n - 1;
                        if (m >= _im.height)
                            m = 2 * (_im.height - 1) - m + 1;
                        if (n >= _im.width)
                            n = 2 * (_im.width - 1) - n + 1;
                        kernel.push_back(_im(m, n));
                        int c = kernel[k * 3 + l];
                    }
                }
                if (0 == _im.data[i * _im.width + j] || 255 == _im.data[i * _im.width + j]) {
                    std::sort(kernel.begin(), kernel.end());
                    dat[i * _im.width + j] = kernel[4];
                } else {
                    dat[i * _im.width + j] = _im.data[i * _im.width + j];
                }
                kernel.clear();
            }
        }

        return Image(_im.width, _im.height, 1, dat);
    }

    Image pepper_salt_noise(Image &_im, int cnt) {
        LI_U8 *dat = new LI_U8[_im.width * _im.height];

        for (int j = 0; j < _im.height; ++j) {
            for (int i = 0; i < _im.width; ++i) {
                dat[j * _im.width + i] = _im(j, i);
            }
        }

        srand((unsigned int) time(0));
        for (int i = 0; i < cnt; ++i) {
            int rw = rand() % _im.width;
            int rh = rand() % _im.height;
            dat[rh * _im.width + rw] = 0;
            rw = rand() % _im.width;
            rh = rand() % _im.height;
            dat[rh * _im.width + rw] = 255;
        }

        return Image(_im.width, _im.height, 1, dat);
    }


    Image base_filter(Image &_im, Filter_kernel &kernel) {
        double *ddat = new double[_im.width * _im.height];

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                double val = 0;
                for (int k = 0; k < kernel.rows; ++k) {
                    for (int l = 0; l < kernel.cols; ++l) {
                        int m = i + k - 1;
                        int n = j + l - 1;
                        if (m < 0)
                            m = -m - 1;
                        if (n < 0)
                            n = -n - 1;
                        if (m >= _im.height)
                            m = 2 * (_im.height - 1) - m + 1;
                        if (n >= _im.width)
                            n = 2 * (_im.width - 1) - n + 1;
                        val += _im(m, n) * kernel(k, l);
                    }
                }
                ddat[i * _im.width + j] = val;
            }
        }

        LI_U8 *dat = new LI_U8[_im.width * _im.height];

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                int p = (int) (ddat[i * _im.width + j]);
                if (p > 255)
                    p = 255;
                if (p < 0)
                    p = 0;
                dat[i * _im.width + j] = (LI_U8) p;
            }
        }
        return Image(_im.width, _im.height, 1, dat);
    }
}