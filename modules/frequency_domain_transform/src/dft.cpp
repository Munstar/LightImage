//
// Created by xin on 12/19/15.
//

#include "../include/dft.h"
#include <complex>
#include <cmath>

namespace li {

/*
    Image dft(Image& _im)
    {
        complex<double> * cdat = new complex<double >[_im.width * _im.height];

        LI_U8 *ptr_ori = _im.data;
        complex<double> *ptr_com = cdat;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                ptr_com[i * _im.width + j] = 0;
                for (int k = 0; k < _im.height; ++k) {
                    for (int l = 0; l < _im.width; ++l) {
                        double rad = -2*lipi *((double)(k*i)/(double)(_im.height)+(double)(l*j)/(double)(_im.width));
                        double f = (double)(ptr_ori[k * _im.width + l]);
                        if((k+l)%2)
                            f = -1*f;
                        ptr_com[i * _im.width + j] += complex<double>(f * cos(rad), f * sin(rad));
                    }
                }
                std::cout<<"Height: "<<i<<"  Width: "<<j<<std::endl;
            }
        }

        LI_U8 * dat = new LI_U8[_im.width * _im.height];
        LI_U8 * ptr_new = dat;
        ptr_com = cdat;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                complex<double> c = ptr_com[i * _im.width + j];
                ptr_new[i * _im.width + j] = (LI_U8)(sqrt(c.real()*c.real()+c.imag()*c.imag())/(_im.height));
            }
        }

        delete[](cdat);

        return Image(_im.width, _im.height, _im.channels, dat);
    }
*/

/*
    Matrix_<complex<float>> dft(Image& _im)
    {
        complex<float> * cdat = new complex<float>[_im.width * _im.height];

        LI_U8 *ptr_ori = _im.data;
        complex<float> *ptr_com = cdat;

        float *colSinTab = new float[_im.height];
        float *colCosTab = new float[_im.height];
        float *rowSinTab = new float[_im.width];
        float *rowCosTab = new float[_im.width];

        for (int m = 0; m < _im.height; ++m) {
            double rad = -2 * lipi * ((double)m/(double)_im.height);
            colSinTab[m] = sin(rad);
            colCosTab[m] = cos(rad);
        }

        for (int m = 0; m < _im.width; ++m) {
            double rad = -2 * lipi * ((double)m/(double)_im.width);
            rowSinTab[m] = sin(rad);
            rowCosTab[m] = cos(rad);
        }

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                cdat[i * _im.width + j] = 0;
                for (int k = 0; k < _im.width; ++k) {
                    float f = (float)(ptr_ori[i * _im.width + k]);
                    if((k+i)%2)
                        f = -1*f;
                    cdat[i * _im.width + j] += complex<float>(f,0)*complex<float>(rowCosTab[(j*k)%_im.width], rowSinTab[(j*k)%_im.width]);
                }
            }
        }

        complex<float> *temp = new complex<float>[_im.height];
        for (int i = 0; i < _im.width; ++i) {
            for (int j = 0; j < _im.height; ++j) {
                temp[j] = 0;
                for (int k = 0; k < _im.height; ++k) {
                    //float rad = -2 * lipi * ((float)(j*k)/(float)_im.height);
                    temp[j] += ptr_com[k * _im.width + i] * complex<float>(colCosTab[(j*k)%_im.height], colSinTab[(j*k)%_im.height]);
                }
            }
            for (int l = 0; l < _im.height; ++l) {
                ptr_com[l * _im.width + i] = temp[l];
            }
        }

        delete[](temp);



        delete[](rowCosTab);
        delete[](rowSinTab);
        delete[](colCosTab);
        delete[](colSinTab);

        return Matrix_<complex<float>>(_im.width, _im.height, _im.channels, cdat);
    }
*/

    Matrix_<complex<float>> dft(Image &_im) {
        unsigned int newHeightAndWidth = _im.width > _im.height ? _im.width : _im.height;

        if (newHeightAndWidth & (newHeightAndWidth - 1)) {
            double p = ceil(log((double) newHeightAndWidth) / log(2.));
            newHeightAndWidth = (int) pow(2, p);
        }

        complex<float> *cdat = new complex<float>[newHeightAndWidth * newHeightAndWidth];

        double mean = 0.;

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                mean += _im.data[i * _im.width + j];
            }
        }

        mean = mean / (_im.width * _im.height);

        for (int i = 0; i < newHeightAndWidth; ++i) {
            for (int j = 0; j < newHeightAndWidth; ++j) {
                cdat[i * newHeightAndWidth + j] = complex<float>(mean, 0.0);
            }
        }

        for (int i = 0; i < _im.height; ++i) {
            for (int j = 0; j < _im.width; ++j) {
                cdat[i * newHeightAndWidth + j] = complex<float>((float) (_im.data[i * _im.width + j]), 0.0);
            }
        }

        complex<float> *row = new complex<float>[newHeightAndWidth];
        for (int i = 0; i < newHeightAndWidth; ++i) {
            for (int j = 0; j < newHeightAndWidth; ++j) {
                row[j] = cdat[i * newHeightAndWidth + j];
                if ((i + j) % 2)
                    row[j] = complex<float>(-1.0, 0) * row[j];
            }
            fft(row, newHeightAndWidth, false);
            for (int k = 0; k < newHeightAndWidth; ++k) {
                cdat[i * newHeightAndWidth + k] = row[k];
            }
        }

        delete[](row);

        complex<float> *col = new complex<float>[newHeightAndWidth];
        for (int i = 0; i < newHeightAndWidth; ++i) {
            for (int j = 0; j < newHeightAndWidth; ++j) {
                col[j] = cdat[j * newHeightAndWidth + i];
            }
            fft(col, newHeightAndWidth, false);
            for (int k = 0; k < newHeightAndWidth; ++k) {
                cdat[k * newHeightAndWidth + i] = col[k];
            }
        }

        delete[](col);

        return Matrix_<complex<float>>(newHeightAndWidth, newHeightAndWidth, 1, cdat);

    }

/*
    Image idft(Matrix_<complex<float>>& ft)
    {
        complex<float> * cdat = new complex<float>[ft.width * ft.height];

        complex<float> *ptr_ori = ft.data;
        complex<float> *ptr_com = cdat;

        float *colSinTab = new float[ft.height];
        float *colCosTab = new float[ft.height];
        float *rowSinTab = new float[ft.width];
        float *rowCosTab = new float[ft.width];

        for (int m = 0; m < ft.height; ++m) {
            double rad = 2 * lipi * ((double)m/(double)ft.height);
            colSinTab[m] = sin(rad);
            colCosTab[m] = cos(rad);
        }

        for (int m = 0; m < ft.width; ++m) {
            double rad = 2 * lipi * ((double)m/(double)ft.width);
            rowSinTab[m] = sin(rad);
            rowCosTab[m] = cos(rad);
        }

        for (int i = 0; i < ft.height; ++i) {
            for (int j = 0; j < ft.width; ++j) {
                cdat[i * ft.width + j] = 0;
                for (int k = 0; k < ft.width; ++k) {
                    complex<float> f = ptr_ori[i * ft.width + k];
                    //if((k+i)%2)
                        //f = -1*f;
                    cdat[i * ft.width + j] += f * complex<float>(rowCosTab[(j*k)%ft.width], rowSinTab[(j*k)%ft.width]);
                }
            }
        }

        complex<float> *temp = new complex<float>[ft.height];
        for (int i = 0; i < ft.width; ++i) {
            for (int j = 0; j < ft.height; ++j) {
                temp[j] = 0;
                for (int k = 0; k < ft.height; ++k) {
                    //float rad = -2 * lipi * ((float)(j*k)/(float)_im.height);
                    temp[j] += ptr_com[k * ft.width + i] * complex<float>(colCosTab[(j*k)%ft.height], colSinTab[(j*k)%ft.height]);
                }
            }
            for (int l = 0; l < ft.height; ++l) {
                ptr_com[l * ft.width + i] = temp[l];
            }
        }

        delete[](temp);

        LI_U8 * dat = new LI_U8[ft.width * ft.height];
        LI_U8 * ptr_new = dat;
        ptr_com = cdat;

        for (int i = 0; i < ft.height; ++i) {
            for (int j = 0; j < ft.width; ++j) {
                complex<float> c = ptr_com[i * ft.width + j];
                ptr_new[i * ft.width + j] = (LI_U8)(sqrt(c.real()*c.real()+c.imag()*c.imag())/(float)(ft.width * ft.height));
            }
        }

        delete[](cdat);
        delete[](rowCosTab);
        delete[](rowSinTab);
        delete[](colCosTab);
        delete[](colSinTab);

        return Image(ft.width, ft.height, ft.channels, dat);
    }
*/

    Image butterworth_filter(Image &_im, double d0, int level) {
        Matrix_<complex<float>> ft = dft(_im);

        complex<float> *H = new complex<float>[ft.width * ft.height];

        for (int i = 0; i < ft.height; ++i) {
            for (int j = 0; j < ft.width; ++j) {
                float d = (float) sqrt(
                        (i - ft.height / 2) * (i - ft.height / 2) + (j - ft.width / 2) * (j - ft.width / 2));
                H[i * ft.width + j] = complex<float>(1.0 / (1.0 + pow((d / d0), 2.0 * level)), 0);
            }
        }

        for (int i = 0; i < ft.height; ++i) {
            for (int j = 0; j < ft.width; ++j) {
                ft.data[i * ft.width + j] = ft.data[i * ft.width + j] * H[i * ft.width + j];
            }
        }

        return idft(ft, _im.width, _im.height);
    }

    Image idft(Matrix_<complex<float>> &ft, int width, int height) {
        complex<float> *cdat = new complex<float>[ft.width * ft.height];

        complex<float> *ptr_ori = ft.data;
        complex<float> *ptr_com = cdat;

        complex<float> *row = new complex<float>[ft.width];
        for (int i = 0; i < ft.height; ++i) {
            for (int j = 0; j < ft.width; ++j) {
                row[j] = ptr_ori[i * ft.width + j];
            }
            fft(row, ft.width, true);
            for (int k = 0; k < ft.width; ++k) {
                ptr_com[i * ft.width + k] = row[k];
            }
        }

        delete[](row);

        complex<float> *col = new complex<float>[ft.height];
        for (int i = 0; i < ft.width; ++i) {
            for (int j = 0; j < ft.height; ++j) {
                col[j] = ptr_com[j * ft.width + i];
            }
            fft(col, ft.height, true);
            for (int k = 0; k < ft.height; ++k) {
                ptr_com[k * ft.width + i] = col[k];
            }
        }
        delete[](col);

        LI_U8 *dat = new LI_U8[width * height];
        LI_U8 *ptr_new = dat;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                complex<float> c = ptr_com[i * ft.width + j];
                ptr_new[i * width + j] = (LI_U8) (sqrt(c.real() * c.real() + c.imag() * c.imag()) /
                                                  (float) (ft.width * ft.height));
            }
        }

        delete[](cdat);

        return Image(width, height, 1, dat);
    }

    Image renderPowerSpectrum(Matrix_<complex<float>> &ft) {
        LI_U8 *dat = new LI_U8[ft.width * ft.height];
        float *fdat = new float[ft.width * ft.height];

        complex<float> *ptr_ori = ft.data;

        float min = 255.0;
        float max = 0.0;
        for (int i = 0; i < ft.height; ++i) {
            for (int j = 0; j < ft.width; ++j) {
                complex<float> c = ptr_ori[i * ft.width + j];
                float p = sqrt(c.real() * c.real() + c.imag() * c.imag()) / (ft.width * ft.height);
                fdat[i * ft.width + j] = p;
                if (p >= max)
                    max = p;
                if (p <= min)
                    min = p;
            }
        }

        for (int i = 0; i < ft.height; ++i) {
            for (int j = 0; j < ft.width; ++j) {
                dat[i * ft.width + j] = (LI_U8) (pow((fdat[i * ft.width + j] - min) / (max - min), 0.15) * 255.0);
            }
        }

        delete[](fdat);
        return Image(ft.width, ft.height, ft.channels, dat);
    }


    void fft(complex<float> *dat, int n, bool inverse) {
        unsigned int N = (unsigned) n;

        unsigned int Target = 0;

        for (unsigned int Position = 0; Position < N; ++Position) {
            if (Target > Position) {
                complex<float> Temp(dat[Target]);
                dat[Target] = dat[Position];
                dat[Position] = Temp;
            }

            unsigned int Mask = N;

            while (Target & (Mask >>= 1))
                Target &= ~Mask;

            Target |= Mask;
        }

        const double pi = inverse ? 3.14159265358979323846 : -3.14159265358979323846;

        for (unsigned int Step = 1; Step < N; Step <<= 1) {
            const unsigned int Jump = Step << 1;

            const double delta = pi / (double) (Step);

            const double Sine = sin(delta * 0.5);

            const complex<float> Multiplier(-2. * Sine * Sine, sin(delta));

            complex<float> Factor(1., 0.);

            for (unsigned int Group = 0; Group < Step; ++Group) {
                for (unsigned int Pair = Group; Pair < N; Pair += Jump) {
                    const unsigned int Match = Pair + Step;

                    const complex<float> Product(Factor * dat[Match]);

                    dat[Match] = dat[Pair] - Product;

                    dat[Pair] = dat[Pair] + Product;
                }

                Factor = Multiplier * Factor + Factor;
            }
        }
    }
}
