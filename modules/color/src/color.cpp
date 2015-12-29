//
// Created by xin on 12/21/15.
//

#include "../include/color.h"

namespace li {
    Image rgb2gray(Image &_im) {
        LI_U8 *dat = new LI_U8[_im.width * _im.height];
        LI_U8 *ptr_ori = _im.data;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                int temp = 0;
                for (int k = 0; k < _im.channels; ++k) {
                    temp += ptr_ori[(i * _im.width + j) * _im.channels + k];
                }
                dat[i * _im.width + j] = temp / _im.channels;
            }
        }

        return Image(_im.width, _im.height, 1, dat);
    }
}