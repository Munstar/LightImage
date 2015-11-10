
#include <iostream>
#include "modules/core/include/core.hpp"
#include "modules/io/include/io.h"


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

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    char fname[] = "/home/xin/Pictures/lena_grayscale.bmp";
    Matrix_<LI_U8> img;
    img = imload(fname);

    QImage im(img.data, img.width, img.height, QImage::Format_RGB888);

    QLabel* l = new QLabel();
    l->setPixmap(QPixmap::fromImage(im));
    l->show();

    return app.exec();
}