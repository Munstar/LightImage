//
// Created by xin on 11/17/15.
//

#include "../include/histogram.h"


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


        int cnt_per_pix = max / _height;

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
}