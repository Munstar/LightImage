#include "../include/histogram.h"
#include "LightImage.h"


namespace li {
    Histogram::Histogram() : channles(0), data(NULL) {

    }

    Histogram::Histogram(Image &_im) {
        channles = _im.channels;
        data = new int[channles * 256];

        for (int j = 0; j < 256 * channles; ++j) {
            data[j] = 0;
        }


        int pix_cnt = _im.width * _im.height;
        for (int i = 0; i < pix_cnt; ++i) {
            for (int j = 0; j < _im.channels; ++j) {
                LI_U8 _v = _im.data[i * channles + j];
                data[j * 256 + _v] += 1;
            }
        }
    }

    Histogram::~Histogram() {
        delete[] data;
    }

    Image Histogram::Render(int _width = 256, int _height = 180) {
        LI_U8 *dat = new LI_U8[_width * _height * channles];

        int max = 0;
        for (int j = 0; j < 256 * channles; ++j) {
            if (data[j] > max)
                max = data[j];
        }


        int cnt_per_pix = (max / _height) + 1;

        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                for (int k = 0; k < channles; ++k) {
                    int _v = data[k * 256 + j];
                    auto h = _height - _v / cnt_per_pix;
                    if (i > h)
                        dat[(i * _width + j) * channles + k] = 255;
                    else
                        dat[(i * _width + j) * channles + k] = 0;
                }
            }
        }

        return Image(_width, _height, channles, dat);
    }

    double hist_simi(Image &_im1, Image &_im2) {
        Image temp1 = rgb2gray(_im1);
        Image temp2 = rgb2gray(_im2);

        Histogram h1(_im1);
        Histogram h2(_im2);

        int max1 = 0;
        int max2 = 0;

        double p1[255] = {0.0};
        double p2[255] = {0.0};

        for (int i = 1; i < 255; ++i) {
            if (h1.data[i] > max1)
                max1 = h1.data[i];
            if (h2.data[i] > max2)
                max2 = h2.data[i];
        }

        for (int j = 1; j < 255; ++j) {
            p1[j] = (double) h1.data[j] / (double) max1;
            p2[j] = (double) h2.data[j] / (double) max2;
        }

        double res = 0.0;

        for (int k = 1; k < 255; ++k) {
            res += abs(p1[k] - p2[k]);
        }

        return 1.0 / res;
    }

    Image histogram_eq(Image &_im) {
        Histogram h(_im);

        for (int i = 1; i < 256; ++i) {
            for (int j = 0; j < h.channles; ++j) {
                h.data[j * 256 + i] = h.data[j * 256 + i] + h.data[j * 256 + i - 1];
            }
        }

        int pix_per_level = (_im.width * _im.height) / 256;

        LI_U8 *map = new LI_U8[h.channles * 256];

        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < h.channles; ++j) {
                map[j * 256 + i] = h.data[j * 256 + i] / pix_per_level;
            }
        }

        LI_U8 *dat = new LI_U8[_im.width * _im.height * _im.channels];
        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                for (int k = 0; k < _im.channels; ++k) {
                    dat[(i * _im.width + j) * _im.channels + k] = map[k * 256 +
                                                                      _im.data[(i * _im.width + j) * _im.channels + k]];
                }
            }
        }

        delete[](map);

        return Image(_im.width, _im.height, _im.channels, dat);
    }
}