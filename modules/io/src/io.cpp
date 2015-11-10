//
// Created by xin on 11/10/15.
//

#include "../include/io.h"
#include "../../core/include/error.hpp"

#include <fstream>

namespace li {
    Matrix_<LI_U8> imload(const char *fname) {
        std::ifstream ifs(fname, std::ifstream::binary);

        if (ifs) {
            BitMapFileHeader *fh = new BitMapFileHeader;
            BitMapInfoHeader *ih = new BitMapInfoHeader;

            ifs.read((char *) fh, sizeof(BitMapFileHeader));
            ifs.read((char *) ih, sizeof(BitMapInfoHeader));

            auto offset = fh->Offset;
            auto width = ih->Width;
            auto height = ih->Height;
            auto bitcnt = ih->BitCount;
            auto imsize = ih->ImageSize;
            int channels = bitcnt / 8;

            LI_U8 *buf = new LI_U8[imsize];
            LI_U8 *img = new LI_U8[width * height * channels];

            ifs.seekg(offset);

            ifs.read((char *) buf, imsize);

            ifs.close();

            auto padding = (width * channels) % 4 ? 4 - (width * channels) % 4 : 0;

            LI_U8 *ptr_buf = buf;
            LI_U8 *ptr_img = img;
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    ptr_img[0] = ptr_buf[2];
                    ptr_img[1] = ptr_buf[1];
                    ptr_img[2] = ptr_buf[0];
                    ptr_buf += channels;
                    ptr_img += channels;
                }
                ptr_buf += padding;
            }

            delete[] buf;
            return Matrix_<LI_U8>(width, height, channels, img);
        } else {
            ERR("Open file failed");
        }
    }
}

