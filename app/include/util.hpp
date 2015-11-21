//
// Created by xin on 11/17/15.
//

#ifndef LIGHTIMAGE_UTIL_HPP
#define LIGHTIMAGE_UTIL_HPP

#include <QtGui/qimage.h>
#include "LightImage.h"


QImage CvtToQImage(li::Matrix_<li::LI_U8> &im) {
    auto padding = (4 - (im.width * 3) % 4) % 4;
    auto step = im.width * 3 + padding;
    li::LI_U8 *_dat = new li::LI_U8[step * im.height];

    li::LI_U8 *ptr_img = im.data;
    li::LI_U8 *ptr_pim = _dat;

    for (int i = 0; i < im.height; ++i) {
        for (int j = 0; j < im.width; ++j) {
            for (int k = 0; k < im.channels; ++k) {
                if (im.channels == 3) {
                    *ptr_pim = *ptr_img;
                    ptr_img++;
                    ptr_pim++;
                } else {
                    if (im.channels == 1) {
                        *ptr_pim = *ptr_img;
                        ptr_pim++;
                        *ptr_pim = *ptr_img;
                        ptr_pim++;
                        *ptr_pim = *ptr_img;
                        ptr_pim++;
                        ptr_img++;
                    }
                }
            }
        }
        ptr_pim += padding;
    }

    return QImage(_dat, im.width, im.height, QImage::Format_RGB888);
}


#endif //LIGHTIMAGE_UTIL_HPP
