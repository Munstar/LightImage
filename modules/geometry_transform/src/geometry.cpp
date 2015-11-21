//
// Created by xin on 11/19/15.
//

#include "../include/geometry.h"
#include <cmath>


namespace li {
    Image mirror(Image &_im, bool hor, bool ver) {
        LI_U8 *dat = new LI_U8[_im.width * _im.height * _im.channels];

        LI_U8 *ptr_ori = _im.data;
        LI_U8 *ptr_new = dat;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                int u = i;
                int v = j;

                if (hor)
                    v = _im.width - j - 1;
                if (ver)
                    u = _im.height - i - 1;

                for (int k = 0; k < _im.channels; ++k) {
                    ptr_new[(i * _im.width + j) * _im.channels + k] = ptr_ori[(u * _im.width + v) * _im.channels + k];
                }
            }
        }

        return Image(_im.width, _im.height, _im.channels, dat);
    }

    Image scale(Image &_im, int _width, int _height) {
        double _fx = (double) _width / (double) _im.width;
        double _fy = (double) _height / (double) _im.height;

        double _v0 = _fx;
        double _v1 = 0.0;
        double _v2 = 0.0;
        double _v3 = 0.0;
        double _v4 = _fy;
        double _v5 = 0.0;
        double _v6 = 0.0;
        double _v7 = 0.0;
        double _v8 = 1.0;

        TransMat T(_v0, _v1, _v2,
                   _v3, _v4, _v5,
                   _v6, _v7, _v8);
        TransMat TI = T.inv();


        LI_U8 *dat = new LI_U8[_width * _height * _im.channels];
        LI_U8 *ptr_dat = dat;

        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                TransVec VT((double) (j - _width / 2), (double) (i - _height / 2), 1.0);
                TransVec VO = VT * TI;
                int u = (int) (VO(0) - 0.50) + _im.width / 2;
                int v = (int) (VO(1) - 0.50) + _im.height / 2;
                for (int k = 0; k < _im.channels; ++k) {
                    if (u >= _im.width || v >= _im.height || u < 0 || v < 0) {
                        ptr_dat[(i * _im.width + j) * _im.channels + k] = 255;
                    }
                    else {
                        ptr_dat[(i * _width + j) * _im.channels + k] = _im.data[(v * _im.width + u) * _im.channels + k];
                    }
                }
            }
        }

        return Image(_width, _height, _im.channels, dat);
    }

    Image rotate(Image &_im, double _angle) {
        double _v0 = cos(_angle / 180 * M_PI);
        double _v1 = sin(_angle / 180 * M_PI);
        double _v2 = 0.0;
        double _v3 = -1 * _v1;
        double _v4 = _v0;
        double _v5 = 0.0;
        double _v6 = 0.0;
        double _v7 = 0.0;
        double _v8 = 1.0;

        TransMat T(_v0, _v1, _v2,
                   _v3, _v4, _v5,
                   _v6, _v7, _v8);
        TransMat TI = T.inv();


        LI_U8 *dat = new LI_U8[_im.width * _im.height * _im.channels];
        LI_U8 *ptr_dat = dat;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                TransVec VT((double) (j - _im.width / 2), (double) (i - _im.height / 2), 1.0);
                TransVec VO = VT * TI;
                int u = (int) (VO(0) - 0.50) + _im.width / 2;
                int v = (int) (VO(1) - 0.50) + _im.height / 2;
                for (int k = 0; k < _im.channels; ++k) {
                    if (u >= _im.width || v >= _im.height || u < 0 || v < 0) {
                        ptr_dat[(i * _im.width + j) * _im.channels + k] = 255;
                    }
                    else {
                        ptr_dat[(i * _im.width + j) * _im.channels + k] = _im.data[(v * _im.width + u) * _im.channels +
                                                                                   k];
                    }
                }
            }
        }

        return Image(_im.width, _im.height, _im.channels, dat);
    }

    Image clip(Image &_im, int x1, int y1, int x2, int y2) {
        int _width = (x2 - x1) > 0 ? x2 - x1 : x1 - x2;
        int _height = (y2 - y1) > 0 ? y2 - y1 : y1 - y2;
        int _channels = _im.channels;
        LI_U8 *dat = new LI_U8[_width * _height * _channels];

        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                for (int k = 0; k < _channels; ++k) {
                    dat[(i * _width + j) * _channels + k] = _im.data[((i + y1) * _im.width + j + x1) * _channels + k];
                }
            }
        }
        return Image(_width, _height, _channels, dat);
    }

    Image move(Image &_im, int x, int y) {
        double _v0 = 1.0;
        double _v1 = 0.0;
        double _v2 = 0.0;
        double _v3 = 0.0;
        double _v4 = 1.0;
        double _v5 = 0.0;
        double _v6 = double(x);
        double _v7 = double(y);
        double _v8 = 1.0;

        TransMat T(_v0, _v1, _v2,
                   _v3, _v4, _v5,
                   _v6, _v7, _v8);
        TransMat TI = T.inv();


        LI_U8 *dat = new LI_U8[_im.width * _im.height * _im.channels];
        LI_U8 *ptr_dat = dat;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                TransVec VT((double) (j - _im.width / 2), (double) (i - _im.height / 2), 1.0);
                TransVec VO = VT * TI;
                int u = (int) (VO(0) - 0.50) + _im.width / 2;
                int v = (int) (VO(1) - 0.50) + _im.height / 2;
                for (int k = 0; k < _im.channels; ++k) {
                    if (u >= _im.width || v >= _im.height || u < 0 || v < 0) {
                        ptr_dat[(i * _im.width + j) * _im.channels + k] = 255;
                    }
                    else {
                        ptr_dat[(i * _im.width + j) * _im.channels + k] = _im.data[(v * _im.width + u) * _im.channels +
                                                                                   k];
                    }
                }
            }
        }

        return Image(_im.width, _im.height, _im.channels, dat);
    }

}