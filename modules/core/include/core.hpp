//
// Created by xin on 11/4/15.
//

#ifndef LIGHTIMAGE_CORE_HPP
#define LIGHTIMAGE_CORE_HPP

#include <cstdio>

#include "point.hpp"
#include "types.h"
#include "matrix.hpp"
#include "error.hpp"

namespace li {
    using namespace std;

    typedef Point2_<li::LI_S32> Point2D32S;
    typedef Point2_<li::LI_F32> Point2D32F;


    template<typename _Tp>
    void print_mat(Matrix_<_Tp> _m) {
        for (int i = 0; i < _m.height; ++i) {
            for (int j = 0; j < _m.width; ++j) {
                for (int k = 0; k < _m.channels; ++k) {
                    printf("%2x", (int) (_m.data[i * _m.width + j * _m.channels + k]));
                }
                printf(" ");
            }
            printf("\n");
        }
    }
}

#endif //LIGHTIMAGE_CORE_HPP
