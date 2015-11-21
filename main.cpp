
#include <iostream>
#include "modules/core/include/core.hpp"
#include "modules/io/include/io.h"
#include "modules/histogram/include/histogram.h"


using namespace std;
using namespace li;

/*
int main() {

    char fname[] = "/home/xin/Pictures/bmptest2.bmp";

    Matrix_<LI_U8> im;
    im = imload(fname);

    print_mat(im);
    return 0;
}
*/

#include <QApplication>
#include <QtWidgets>


QImage CvtToQImage(Matrix_<LI_U8> &im);

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    char fname[] = "/home/xin/Pictures/bmptest.bmp";
    Image img;
    img = imload(fname);

    Histogram *h = new Histogram(img);
    Image imh = h->Render(256, 180);

    QImage im1 = CvtToQImage(img);
    QImage im2 = CvtToQImage(imh);
    //QImage im(dat, 3, 3, QImage::Format_RGB888);
    im1 = im1.mirrored(false, true);
    im2 = im2.mirrored(false, true);
    QLabel *l1 = new QLabel();
    l1->setPixmap(QPixmap::fromImage(im1));
    l1->show();


    QLabel *l2 = new QLabel();
    l2->setPixmap(QPixmap::fromImage(im2));
    l2->show();

    return app.exec();
}

QImage CvtToQImage(Matrix_<LI_U8> &im) {
    auto padding = (4 - (im.width * 3) % 4) % 4;
    auto step = im.width * 3 + padding;
    LI_U8 *_dat = new LI_U8[step * im.height];

    LI_U8 *ptr_img = im.data;
    LI_U8 *ptr_pim = _dat;

    for (int i = 0; i < im.height; ++i) {
        for (int j = 0; j < im.width; ++j) {
            for (int k = 0; k < im.channels; ++k) {
                if (im.channels == 3) {
                    *ptr_pim = *ptr_img;
                    ptr_img++;
                    ptr_pim++;
                } else {
                    if (im.channels == 1) {
                        *ptr_pim = *ptr_img;
                        ptr_pim++;
                        *ptr_pim = *ptr_img;
                        ptr_pim++;
                        *ptr_pim = *ptr_img;
                        ptr_pim++;
                        ptr_img++;
                    }
                }
            }
        }
        ptr_pim += padding;
    }

    return QImage(_dat, im.width, im.height, QImage::Format_RGB888);
}