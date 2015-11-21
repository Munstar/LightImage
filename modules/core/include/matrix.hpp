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


    template<typename _Tp, int m, int n>
    class MiniMat {
    public:

        MiniMat();

        MiniMat(_Tp _v0, _Tp _v1, _Tp _v2);

        MiniMat(_Tp _v0, _Tp _v1, _Tp _v2, _Tp _v3, _Tp _v4, _Tp _v5, _Tp _v6, _Tp _v7, _Tp _v8);

        const _Tp &operator()(int i, int j) const;

        const _Tp &operator()(int i) const;

        void operator=(MiniMat &_m) const;

        const _Tp det() const;

        const MiniMat inv() const;

        template<typename _Tp2, int m1, int m2>
        const MiniMat operator*(MiniMat<_Tp2, m1, m2> &_m) const;

        _Tp data[m * n];
        const int rows = m;
        const int clos = n;
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

    template<typename _Tp, int m, int n>
    inline
    const _Tp &MiniMat<_Tp, m, n>::operator()(int i, int j) const {
        return data[i * n + j];
    }

    template<typename _Tp, int m, int n>
    MiniMat<_Tp, m, n>::MiniMat() {
        for (int i = 0; i < m * n; ++i) {
            data[i] = _Tp(0);
        }
    }

    template<typename _Tp, int m, int n>
    MiniMat<_Tp, m, n>::MiniMat(_Tp _v0, _Tp _v1, _Tp _v2) {
        data[0] = _v0;
        data[1] = _v1;
        data[2] = _v2;
    }

    template<typename _Tp, int m, int n>
    MiniMat<_Tp, m, n>::MiniMat(_Tp _v0, _Tp _v1, _Tp _v2, _Tp _v3, _Tp _v4, _Tp _v5, _Tp _v6, _Tp _v7, _Tp _v8) {
        data[0] = _v0;
        data[1] = _v1;
        data[2] = _v2;
        data[3] = _v3;
        data[4] = _v4;
        data[5] = _v5;
        data[6] = _v6;
        data[7] = _v7;
        data[8] = _v8;
    }

    template<typename _Tp, int m, int n>
    const _Tp MiniMat<_Tp, m, n>::det() const {
        if (m == n && m == 3) {
            _Tp temp = data[0 * n + 0] * (data[1 * n + 1] * data[2 * n + 2] - data[2 * n + 1] * data[1 * n + 2]) -
                       data[0 * n + 1] * (data[1 * n + 0] * data[2 * n + 2] - data[2 * n + 0] * data[1 * n + 2]) +
                       data[0 * n + 2] * (data[1 * n + 0] * data[2 * n + 1] - data[2 * n + 0] * data[1 * n + 1]);
            return _Tp(temp);
        } else {
            return _Tp(0);
        }
    }

    template<typename _Tp, int m, int n>
    const MiniMat<_Tp, m, n> MiniMat<_Tp, m, n>::inv() const {

        double d = data[0 * n + 0] * (data[1 * n + 1] * data[2 * n + 2] - data[2 * n + 1] * data[1 * n + 2]) -
                   data[0 * n + 1] * (data[1 * n + 0] * data[2 * n + 2] - data[2 * n + 0] * data[1 * n + 2]) +
                   data[0 * n + 2] * (data[1 * n + 0] * data[2 * n + 1] - data[2 * n + 0] * data[1 * n + 1]);

        d = 1.0 / d;
        double _v0 = (data[1 * n + 1] * data[2 * n + 2] - data[1 * n + 2] * data[2 * n + 1]) * d;
        double _v1 = (data[0 * n + 2] * data[2 * n + 1] - data[0 * n + 1] * data[2 * n + 2]) * d;
        double _v2 = (data[0 * n + 1] * data[1 * n + 2] - data[0 * n + 2] * data[1 * n + 1]) * d;

        double _v3 = (data[1 * n + 2] * data[2 * n + 0] - data[1 * n + 0] * data[2 * n + 2]) * d;
        double _v4 = (data[0 * n + 0] * data[2 * n + 2] - data[0 * n + 2] * data[2 * n + 0]) * d;
        double _v5 = (data[0 * n + 2] * data[1 * n + 0] - data[0 * n + 0] * data[1 * n + 2]) * d;

        double _v6 = (data[1 * n + 0] * data[2 * n + 1] - data[1 * n + 1] * data[2 * n + 0]) * d;
        double _v7 = (data[0 * n + 1] * data[2 * n + 0] - data[0 * n + 0] * data[2 * n + 1]) * d;
        double _v8 = (data[0 * n + 0] * data[1 * n + 1] - data[0 * n + 1] * data[1 * n + 0]) * d;

        return MiniMat<_Tp, m, n>(_v0, _v1, _v2, _v3, _v4, _v5, _v6, _v7, _v8);
    }

    template<typename _Tp1, int m, int n>
    template<typename _Tp2, int m1, int m2>
    const MiniMat<_Tp1, m, n> MiniMat<_Tp1, m, n>::operator*(MiniMat<_Tp2, m1, m2> &_m) const {
        double _v0 = data[0 * m1 + 0] * _m(0, 0) + data[0 * m1 + 1] * _m(1, 0) + data[0 * m1 + 2] * _m(2, 0);
        double _v1 = data[0 * m1 + 0] * _m(0, 1) + data[0 * m1 + 1] * _m(1, 1) + data[0 * m1 + 2] * _m(2, 1);
        double _v2 = data[0 * m1 + 0] * _m(0, 2) + data[0 * m1 + 1] * _m(1, 2) + data[0 * m1 + 2] * _m(2, 2);

        return MiniMat<_Tp1, m, n>(_v0, _v1, _v2);
    }

    template<typename _Tp, int m, int n>
    const _Tp &MiniMat<_Tp, m, n>::operator()(int i) const {
        return data[i];
    }

    template<typename _Tp, int m, int n>
    void MiniMat<_Tp, m, n>::operator=(MiniMat<_Tp, m, n> &_m) const {
        for (int i = 0; i < m * n; ++i) {
            data[i] = _m.data[i];
        }
    }
}
#endif //LIGHTIMAGE_MATRIX_HPP
