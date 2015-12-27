//
// Created by xin on 11/10/15.
//

#include "../include/io.h"
#include "../../core/include/error.hpp"

#include <fstream>

namespace li {
    /*
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
*/


    bool imsave(Image &_im, const char *fname) {
        BitMapFileHeader *fh = new BitMapFileHeader;
        BitMapInfoHeader *ih = new BitMapInfoHeader;

        int width = _im.width;
        int height = _im.height;
        int channels = _im.channels;


        int padding = (width * channels) % 4 ? 4 - (width * channels) % 4 : 0;
        int step = width * channels + padding;
        int imgSize = step * height;

        ih->InfoSize = sizeof(BitMapInfoHeader);
        ih->Height = height;
        ih->Width = width;
        ih->Planes = 1;
        ih->BitCount = 8 * channels;
        ih->Compression = 0;
        ih->ImageSize = imgSize;
        ih->HResolution = 2835;
        ih->VResolution = 2835;
        ih->ColorCount = 0;
        ih->ColorImportant = 0;


        fh->Type[0] = 'B';
        fh->Type[1] = 'M';
        fh->Reserved1 = 0;
        fh->Reserved2 = 0;
        fh->Offset = sizeof(BitMapFileHeader) + sizeof(BitMapInfoHeader);
        fh->FileSize = imgSize + fh->Offset;

        LI_U8 *colorTab = new LI_U8[256 * 4];\
        LI_U8 *ptr_tab = colorTab;
        for (int i = 0; i < 256; ++i) {
            ptr_tab[0] = i;
            ptr_tab[1] = i;
            ptr_tab[2] = i;
            ptr_tab[3] = 0;

            ptr_tab += 4;
        }

        if (channels == 1) {
            ih->ColorCount = 256;
            fh->Offset += 256 * 4;
            fh->FileSize += 256 * 4;
        }

        LI_U8 *buf = new LI_U8[step * height];

        LI_U8 *ptr_buf = buf + (height - 1) * step;
        LI_U8 *ptr_img = _im.data;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (channels == 3) {
                    ptr_buf[2] = ptr_img[0];
                    ptr_buf[1] = ptr_img[1];
                    ptr_buf[0] = ptr_img[2];
                } else {
                    if (channels == 1)
                        ptr_buf[0] = ptr_img[0];
                }
                ptr_buf += channels;
                ptr_img += channels;
            }
            ptr_buf += padding;
            ptr_buf -= 2 * step;
        }

        std::ofstream ofs(fname, std::ofstream::binary);

        if (ofs) {
            ofs.write((char *) fh, sizeof(BitMapFileHeader));
            ofs.write((char *) ih, sizeof(BitMapInfoHeader));
            if (channels == 1) {
                ofs.write((char *) colorTab, 1024);
            }
            ofs.write((char *) buf, imgSize);
            ofs.close();

        } else {
            delete[](buf);
            delete(ih);
            delete(fh);
            delete[](colorTab);
            ERR("Open file failed");
        }
        delete[](buf);
        delete(ih);
        delete(fh);
        delete[](colorTab);

        return true;
    }

    Image imload(const char *fname) {
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
            //auto step = (width + padding) * channels;
            auto step = width * channels + padding;

            LI_U8 *ptr_buf = buf + (height - 1) * step;
            LI_U8 *ptr_img = img;
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (channels == 3) {
                        ptr_img[0] = ptr_buf[2];
                        ptr_img[1] = ptr_buf[1];
                        ptr_img[2] = ptr_buf[0];
                    } else {
                        if (channels == 1)
                            ptr_img[0] = ptr_buf[0];
                    }
                    ptr_buf += channels;
                    ptr_img += channels;
                }
                ptr_buf += padding;
                ptr_buf -= 2 * step;
            }

            delete[] buf;
            delete fh;
            delete ih;

            return Image(width, height, channels, img);
        } else {
            ERR("Open file failed");
        }
    }
}

