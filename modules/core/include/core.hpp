#ifndef LIGHTIMAGE_CORE_HPP
#define LIGHTIMAGE_CORE_HPP

#define lipi 3.14159265358979323846

#include <cstdio>

#include "point.hpp"
#include "types.h"
#include "matrix.hpp"
#include "error.hpp"
#include "image.h"

namespace li {
    using namespace std;

    typedef Point2_<li::LI_S32> Point2D32S;
    typedef Point2_<li::LI_F32> Point2D32F;
    typedef MiniMat<double, 3, 3> TransMat;
    typedef MiniMat<double, 3, 1> TransVec;
    typedef MiniMat<double, 3, 3> Filter_kernel;


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

    template<typename _Tp, int m, int n>
    void print_mat(MiniMat<_Tp, m, n> _m) {
        for (int i = 0; i < _m.rows; ++i) {
            for (int j = 0; j < _m.cols; ++j) {
                printf("%lf", (double) _m(i, j));
                printf(" ");
            }
            printf("\n");
        }
    }
}

#endif //LIGHTIMAGE_CORE_HPP
