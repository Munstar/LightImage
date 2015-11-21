//
// Created by xin on 11/17/15.
//

#include "../include/mainwindow.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
