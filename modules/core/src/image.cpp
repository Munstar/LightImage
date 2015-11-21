//
// Created by xin on 11/10/15.
//

/*
#include "../include/image.h"

namespace li
{
    Image::Image() : format(Format::Invalid) {
        Matrix_<LI_U8>();
    }

    Image::Image(int _width, int _height, Format _format) : format(_format)
    {
        int channels = 0;
        switch (_format)
        {
            case GrayScale:
                channels = 1;
                break;
            case RGB888:
                channels = 3;
                break;
            case RGBA8888:
                channels = 4;
                break;
            default:
                channels = 0;
                break;
        }
        Matrix_<LI_U8 >(_width, _height, channels);
    }

    Image::Image(int _width, int _height, Format _format, LI_U8 *_data) : format(_format)
    {
        int channels = 0;
        switch (_format)
        {
            case GrayScale:
                channels = 1;
                break;
            case RGB888:
                channels = 3;
                break;
            case RGBA8888:
                channels = 4;
                break;
            default:
                channels = 0;
                break;
        }
        Matrix_<LI_U8 >(_width, _height, channels, _data);
    }

    Image::Image(int _width, int _height, Format _format, LI_U8 _value) : format(_format)
    {
        int channels = 0;
        switch (_format)
        {
            case GrayScale:
                channels = 1;
                break;
            case RGB888:
                channels = 3;
                break;
            case RGBA8888:
                channels = 4;
                break;
            default:
                channels = 0;
                break;
        }
        Matrix_<LI_U8 >(_width, _height, channels, _value);
    }

    Image::Image(Image& _im)
    {
        width = _im.width;
        height = _im.height;
        channels = _im.channels;
        format = _im.format;

        data = _im.data;
        refcnt = _im.refcnt;
        (*refcnt)++;
    }
}

 */