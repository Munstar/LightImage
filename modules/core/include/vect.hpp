//
// Created by xin on 11/5/15.
//

#ifndef LIGHTIMAGE_VEC_H
#define LIGHTIMAGE_VEC_H

#include <iostream>
#include "error.hpp"

namespace li {
    template<typename _Tp>
    class Vect_ {
    public:
        Vect_();

        Vect_(int _dims);

        Vect_(int _dims, _Tp value);

        Vect_(int _dims, _Tp *_data);

        Vect_(Vect_<_Tp> &_v);

        ~Vect_();

        void release();


        Vect_<_Tp> &operator=(Vect_<_Tp> v);

        Vect_ operator+(Vect_<_Tp> &_v);

        Vect_ operator-(Vect_<_Tp> &_v);

        Vect_ operator*(Vect_<_Tp> &_v);

        Vect_ operator*(_Tp _s);


        int dims;

        int *refcnt;
        _Tp *data;
    };

    template<typename _Tp>
    Vect_<_Tp>::Vect_() : dims(0), refcnt(NULL), data(NULL) { }

    template<typename _Tp>
    Vect_<_Tp>::Vect_(int _dims) : dims(_dims) {
        refcnt = new int(1);
        data = new _Tp[_dims];
    }

    template<typename _Tp>
    Vect_<_Tp>::Vect_(int _dims, _Tp value) : dims(_dims) {
        refcnt = new int(1);
        data = new _Tp[_dims];

        for (int i = 0; i < _dims; ++i) {
            data[i] = value;
        }
    }

    template<typename _Tp>
    Vect_::Vect_(int _dims, _Tp *_data) : dims(_dims) {
        refcnt = new int(1);
        data = _data;
    }

    template<typename _Tp>
    void Vect_<_Tp>::release() {
        if (data) {
            (*refcnt)--;
            if ((*refcnt) == 0) {
                delete[] data;
                delete refcnt;
            }
        }
    }

    template<typename _Tp>
    Vect_<_Tp>::~Vect_() {
        release();
    }

    template<typename _Tp>
    Vect_<_Tp>::Vect_(Vect_<_Tp> &_v) {
        dims = _v.dims;
        refcnt = _v.refcnt;
        data = _v.data;
        (*refcnt)++;
    }

    template<typename _Tp>
    Vect_<_Tp> &Vect_::operator=(Vect_<_Tp> _v) {
        release();

        dims = _v.dims;
        refcnt = _v.refcnt;
        data = _v.data;
        (*refcnt)++;

        return *this;
    }

    template<typename _Tp>
    Vect_ Vect_<_Tp>::operator+(Vect_<_Tp> &_v) {
        if (dims == _v.dims) {
            _Tp *_data = new _Tp[dims];
            for (int i = 0; i < dims; ++i) {
                _data[i] = data[i] + _v.data[i];
            }
            return Vect_(dims, data);
        } else {
            ERR("The dims of the vectors must be same");
        }
    }

    template<typename _Tp>
    Vect_ Vect_<_Tp>::operator-(Vect_<_Tp> &_v) {
        if (dims == _v.dims) {
            _Tp *_data = new _Tp[dims];
            for (int i = 0; i < dims; ++i) {
                _data[i] = data[i] - _v.data[i];
            }
            return Vect_(dims, data);
        } else {
            ERR("The dims of the vectors must be same");
        }
    }

    template<typename _Tp>
    Vect_ Vect_<_Tp>::operator*(Vect_<_Tp> &_v) {
        if (dims == _v.dims) {
            _Tp *_data = new _Tp[dims];
            for (int i = 0; i < dims; ++i) {
                _data[i] = data[i] * _v.data[i];
            }
            return Vect_(dims, data);
        } else {
            ERR("The dims of the vectors must be same");
        }
    }

    template<typename _Tp>
    Vect_ Vect_<_Tp>::operator*(_Tp _s) {
        if (dims > 0) {
            _Tp *_data = new _Tp[dims];
            for (int i = 0; i < dims; ++i) {
                _data[i] = data[i] * _s;
            }
            return Vect_(dims, data);
        } else {
            ERR("The dims of the vectors must be same");
        }
    }
}
#endif //LIGHTIMAGE_VEC_H


