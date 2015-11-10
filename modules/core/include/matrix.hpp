//
// Created by xin on 11/4/15.
//

#ifndef LIGHTIMAGE_MATRIX_HPP
#define LIGHTIMAGE_MATRIX_HPP

#include "error.hpp"

namespace li {

    template<typename _Tp>
    class Matrix_ {
    public:
        Matrix_();

        ~Matrix_();

        void release();

        Matrix_(int _width, int _height, int _channels);

        Matrix_(int _width, int _height, int _channels, _Tp value);

        Matrix_(int _width, int _height, int _channels, _Tp *_data);

        Matrix_(const Matrix_ &_m);

        Matrix_ &operator=(const Matrix_ &_m);

        Matrix_ operator+(const Matrix_ &_m);

        Matrix_ operator-(const Matrix_ &_m);

        Matrix_ operator*(const Matrix_ &_m);

        Matrix_ operator*(_Tp _s);

        //Matrix_ T(const Matrix_ &_m);

    public:
        int width;
        int height;
        int channels;

        int *refcnt;

        _Tp *data;
    };

    template<typename _Tp>
    Matrix_<_Tp>::Matrix_() : width(0), height(0), channels(0), refcnt(NULL), data(NULL) { }

    template<typename _Tp>
    Matrix_<_Tp>::Matrix_(int _width, int _height, int _channels) : width(_width), height(_height),
                                                                    channels(_channels) {
        int cnt = _width * _height * _channels;
        data = new _Tp[cnt];
        refcnt = new int(1);
    }

    template<typename _Tp>
    Matrix_<_Tp>::Matrix_(int _width, int _height, int _channels, _Tp _value) : width(_width), height(_height),
                                                                                channels(_channels) {
        int cnt = _width * _height * _channels;
        data = new _Tp[cnt];

        for (int i = 0; i < cnt; i++) {
            data[i] = _value;
        }

        refcnt = new int(1);
    }

    template<typename _Tp>
    Matrix_<_Tp>::Matrix_(int _width, int _height, int _channels, _Tp *_data) {
        width = _width;
        height = _height;
        channels = _channels;
        refcnt = new int(1);
        data = _data;
    }

    template<typename _Tp>
    Matrix_<_Tp>::~Matrix_() {
        release();
    }

    template<typename _Tp>
    void Matrix_<_Tp>::release() {
        if (data) {
            (*refcnt)--;
            if ((*refcnt) == 0) {
                delete[] data;
                delete refcnt;
            }
        }
    }

    template<typename _Tp>
    Matrix_<_Tp>::Matrix_(const li::Matrix_<_Tp> &_m) {
        width = _m.width;
        height = _m.height;
        channels = _m.height;

        data = _m.data;
        refcnt = _m.refcnt;
        (*refcnt)++;


    }

    template<typename _Tp>
    Matrix_<_Tp> &Matrix_<_Tp>::operator=(const Matrix_<_Tp> &_m) {
        release();

        width = _m.width;
        height = _m.height;
        channels = _m.channels;
        refcnt = _m.refcnt;
        (*refcnt)++;
        data = _m.data;

        return *this;
    }

    template<typename _Tp>
    Matrix_<_Tp> Matrix_<_Tp>::operator+(const li::Matrix_<_Tp> &_m) {
        if (width == _m.width && height == _m.height && channels == _m.channels) {
            int cnt = width * height * channels;
            _Tp *_data = new _Tp[cnt];

            for (int i = 0; i < cnt; ++i) {
                _data[i] = data[i] + _m.data[i];
            }

            return Matrix_<_Tp>(width, height, channels, _data);
        } else {
            ERR("The type of the matrixes must be same.");
        }
    }

    template<typename _Tp>
    Matrix_<_Tp> Matrix_<_Tp>::operator-(const li::Matrix_<_Tp> &_m) {
        if (width == _m.width && height == _m.height && channels == _m.channels) {
            int cnt = width * height * channels;
            _Tp *_data = new _Tp[cnt];

            for (int i = 0; i < cnt; ++i) {
                _data[i] = data[i] - _m.data[i];
            }

            return Matrix_<_Tp>(width, height, channels, _data);
        } else {
            ERR("The type of the matrixes must be same.");
        }
    }

    template<typename _Tp>
    Matrix_<_Tp> Matrix_<_Tp>::operator*(const li::Matrix_<_Tp> &_m) {
        if (width == _m.width && height == _m.height && channels == _m.channels) {
            int cnt = width * height * channels;
            _Tp *_data = new _Tp[cnt];

            for (int i = 0; i < cnt; ++i) {
                _data[i] = data[i] * _m.data[i];
            }

            return Matrix_<_Tp>(width, height, channels, _data);
        } else {
            ERR("The type of the matrixes must be same.");
        }
    }

    template<typename _Tp>
    Matrix_<_Tp> Matrix_<_Tp>::operator*(_Tp _s) {
        if (width > 0 && height > 0 && channels > 0) {
            int cnt = width * height * channels;
            _Tp *_data = new _Tp[cnt];

            for (int i = 0; i < cnt; ++i) {
                _data[i] = data[i] * _s;
            }

            return Matrix_<_Tp>(width, height, channels, _data);
        } else {
            ERR("The type of the matrixes must be same.");
        }
    }
}
#endif //LIGHTIMAGE_MATRIX_HPP
