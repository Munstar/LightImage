//
// Created by xin on 12/19/15.
//

#include "../include/dct.h"
#include "../include/dft.h"

namespace li {
    /*
        Matrix_<float> dct(Image& _im){
            float * cdat = new float[_im.width * _im.height];
            LI_U8 * ptr_ori = _im.data;

            for (int i = 0; i < _im.height; ++i) {
                for (int j = 0; j < _im.width; ++j) {
                    cdat[i * _im.width + j] = 0;
                    for (int k = 0; k < _im.width; ++k) {
                        float c = (float)ptr_ori[i * _im.width + k];
                        float rad = (float) ((2 * k + 1) * j) * lipi / (2 * _im.width);
                        cdat[i * _im.width + j] += c * cos(rad);
                    }
                    cdat[i * _im.width + j] = sqrt(2.0/_im.width) * cdat[i * _im.width + j];
                }
                cdat[i * _im.width] = 1.0/sqrt(2.0) * cdat[i * _im.width];
            }

            float * temp = new float[_im.height];
            for (int i = 0; i < _im.width; ++i) {
                for (int j = 0; j < _im.height; ++j) {
                    temp[j] = 0;
                    for (int k = 0; k < _im.height; ++k) {
                        float c = cdat[k * _im.width + i];
                        float rad = (float) ((2 * k + 1) * j) * lipi / (2 * _im.height);
                        temp[j] += c * cos(rad);
                    }
                }
                for (int l = 0; l < _im.height; ++l) {
                    cdat[l * _im.width + i] = temp[l] * sqrt(2.0/_im.height);
                }
                cdat[i] = 1.0/sqrt(2.0) * cdat[i];
            }

            return Matrix_<float>(_im.width, _im.height, _im.channels, cdat);
        }

        Image idct(Matrix_<float>& _ct){
            float * cdat = new float[_ct.width * _ct.height];
            float * ptr_ori = _ct.data;

            for (int i = 0; i < _ct.width; ++i) {
                for (int j = 0; j < _ct.height; ++j) {
                    cdat[j * _ct.width + i] = 1.0/sqrt(_ct.height) * ptr_ori[i];
                    for (int k = 1; k < _ct.height; ++k) {
                        float c = ptr_ori[k * _ct.width + i];
                        float rad = (float) ((2 * k + 1) * j) * lipi / (2 * _ct.height);
                        cdat[j * _ct.width + i] += sqrt(2.0/_ct.height) * c * cos(rad);
                    }
                    //cdat[i * _ct.width + j] = sqrt(2.0/_ct.width) * cdat[i * _ct.width + j];
                }
                //cdat[i * _ct.width] = 1.0/sqrt(2.0) * cdat[i * _ct.width];
            }

            float * temp = new float[_ct.width];
            for (int i = 0; i < _ct.height; ++i) {
                for (int j = 0; j < _ct.width; ++j) {
                    temp[j] = 1.0/sqrt(_ct.width) * cdat[i * _ct.width];
                    for (int k = 1; k < _ct.width; ++k) {
                        float c = cdat[i * _ct.width + k];
                        float rad = (float) ((2 * j + 1) * k) * lipi / (2 * _ct.width);
                        temp[j] += sqrt(2.0/_ct.width) * c * cos(rad);
                    }
                }
                for (int l = 0; l < _ct.width; ++l) {
                    cdat[i * _ct.width + l] = temp[l];
                }
                //cdat[i] = 1.0/sqrt(2.0) * cdat[i];
            }
            delete[](temp);

            LI_U8 * dat = new LI_U8[_ct.width*_ct.height];
            for (int i = 0; i < _ct.height; ++i) {
                for (int j = 0; j < _ct.width; ++j) {
                    dat[i * _ct.width + j] = (LI_U8) (cdat[i * _ct.width + j]);
                }
            }

            delete[](cdat);
            return Image(_ct.width, _ct.height, _ct.channels, dat);
        }
    */
    void fdct(float *dat, int n) {
        int N = n;

        complex<float> *cData = new complex<float>[2 * N];

        for (int i = 0; i < N; ++i) {
            cData[N - i - 1] = complex<float>(dat[i], 0);
            cData[N + i] = complex<float>(dat[i], 0);
        }

        fft(cData, 2 * N, false);

        double eks = 2. * lipi * (N - 0.5) / (2 * N);
        double co = cos(eks);
        double si = sin(eks);
        complex<float> shift = complex<float>(1.0, 0);
        for (int i = 0; i < 2 * N; ++i) {
            cData[i] = cData[i] * shift;
            shift = shift * complex<float>(co, si);
        }

        for (int i = 0; i < N; ++i) {
            dat[i] = cData[i].real() / sqrt(2.0 * N);
        }

        delete[](cData);

        dat[0] = dat[0] / sqrt(2.0);
    }


    Matrix_<float> dct(Image &_im) {
        unsigned int newHeightAndWidth = _im.width > _im.height ? _im.width : _im.height;

        if (newHeightAndWidth & (newHeightAndWidth - 1)) {
            double p = ceil(log((double) newHeightAndWidth) / log(2.));
            newHeightAndWidth = (int) pow(2, p);
        }

        float *cdat = new float[newHeightAndWidth * newHeightAndWidth];

        double mean = 0.;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                mean += _im.data[i * _im.width + j];
            }
        }

        mean = mean / (_im.width * _im.height);

        for (int i = 0; i < newHeightAndWidth; ++i) {
            for (int j = 0; j < newHeightAndWidth; ++j) {
                cdat[i * newHeightAndWidth + j] = mean;
            }
        }

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                cdat[i * newHeightAndWidth + j] = (float) (_im.data[i * _im.width + j]);
            }
        }

        float *row = new float[newHeightAndWidth];
        for (int i = 0; i < newHeightAndWidth; ++i) {
            for (int j = 0; j < newHeightAndWidth; ++j) {
                row[j] = cdat[i * newHeightAndWidth + j];
            }

            fdct(row, newHeightAndWidth);

            for (int k = 0; k < newHeightAndWidth; ++k) {
                cdat[i * newHeightAndWidth + k] = row[k];
            }
        }
        delete[](row);

        float *col = new float[newHeightAndWidth];
        for (int i = 0; i < newHeightAndWidth; ++i) {
            for (int j = 0; j < newHeightAndWidth; ++j) {
                col[j] = cdat[j * newHeightAndWidth + i];
            }

            fdct(col, newHeightAndWidth);

            for (int k = 0; k < newHeightAndWidth; ++k) {
                cdat[k * newHeightAndWidth + i] = col[k];
            }
        }
        delete[](col);

        return Matrix_<float>(newHeightAndWidth, newHeightAndWidth, 1, cdat);
    }

    void ifdct(float *dat, int n) {
        int N = n;
        dat[0] = dat[0] * sqrt(2.0);

        complex<float> *cData = new complex<float>[2 * N];

        for (int i = 0; i < N; ++i) {
            dat[i] = dat[i] * sqrt(2.0 * N);
        }

        for (int i = 1; i < N; ++i) {
            cData[i] = complex<float>(dat[i], 0.);
            cData[2 * N - i] = -complex<float>(dat[i], 0);
        }
        cData[0] = complex<float>(dat[0], 0);

        double eks = 2 * lipi * (N - 0.5) / (2 * N);
        double co = cos(eks);
        double si = sin(eks);
        complex<float> shift = complex<float>(1., 0.);

        for (int i = 0; i < 2 * N; ++i) {
            cData[i] = cData[i] * shift;
            shift = shift * complex<float>(co, si);
        }

        fft(cData, 2 * N, true);

        complex<float> Factor = complex<float>(1.0 / (2.0 * N), 0.0);

        for (unsigned int Pos = 0; Pos < (unsigned int) (2 * N); Pos++) {
            cData[Pos] = cData[Pos] * Factor;
        }

        for (int i = 0; i < N; ++i) {
            dat[i] = cData[N - i].real();
        }
        delete[](cData);

    }

    Image idct(Matrix_<float> &_ct, int width, int height) {
        float *cdat = new float[_ct.width * _ct.height];

        float *row = new float[_ct.width];
        for (int i = 0; i < _ct.height; ++i) {
            for (int j = 0; j < _ct.width; ++j) {
                row[j] = _ct.data[i * _ct.width + j];
            }
            ifdct(row, _ct.width);

            for (int k = 0; k < _ct.width; ++k) {
                cdat[i * _ct.width + k] = row[k];
            }
        }
        delete[](row);

        float *col = new float[_ct.height];
        for (int i = 0; i < _ct.width; ++i) {
            for (int j = 0; j < _ct.height; ++j) {
                col[j] = cdat[j * _ct.width + i];
            }
            ifdct(col, _ct.height);

            for (int k = 0; k < _ct.height; ++k) {
                cdat[k * _ct.width + i] = col[k];
            }
        }
        delete[](col);

        LI_U8 *dat = new LI_U8[width * height];
        LI_U8 *ptr_new = dat;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                ptr_new[i * width + j] = (LI_U8) (cdat[i * _ct.width + j]);
            }
        }

        delete[](cdat);

        return Image(width, height, 1, dat);

    }


    Image renderPowerSpectrum(Matrix_<float> &_ct) {
        LI_U8 *dat = new LI_U8[_ct.width * _ct.height];

        float *ptr_ori = _ct.data;

        float min = 255.0;
        float max = 0.0;
        for (int i = 0; i < _ct.height; ++i) {
            for (int j = 0; j < _ct.width; ++j) {
                float p = abs(ptr_ori[i * _ct.width + j]);
                if (p >= max)
                    max = p;
                if (p <= min)
                    min = p;
            }
        }

        for (int i = 0; i < _ct.height; ++i) {
            for (int j = 0; j < _ct.width; ++j) {
                dat[i * _ct.width + j] = (LI_U8) (pow((abs(ptr_ori[i * _ct.width + j] - min) / (max - min)), 0.15) *
                                                  255.0);
            }
        }

        return Image(_ct.width, _ct.height, _ct.channels, dat);
    }

}