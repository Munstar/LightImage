//
// Created by xin on 11/17/15.
//

#include "../include/mainwindow.h"
#include "../include/mirrordialog.h"
#include "../include/rotatedialog.h"
#include "../include/scaledialog.h"
#include "ui_mainwindow.h"
#include "../include/util.hpp"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    sceneOri = new QGraphicsScene();
    sceneEdit = new QGraphicsScene();

    ui->graphicsViewOri->setScene(sceneOri);
    ui->graphicsViewEdit->setScene(sceneEdit);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/xin/Pictures", tr("Images (*.bmp)"));
    std::cout << filename.toStdString() << std::endl;
    imageOri = li::imload(filename.toStdString().c_str());

    li::Histogram *h = new li::Histogram(imageOri);
    li::Image hist = h->Render(256, 180);

    QImage imh = CvtToQImage(hist);
    QImage imo = CvtToQImage(imageOri);

    ui->labelHist->setPixmap(QPixmap::fromImage(imh));
    sceneOri->clear();
    sceneOri->addPixmap(QPixmap::fromImage(imo));

}

void MainWindow::on_actionMirror_triggered() {
    int para = MirrorDialog::getMirrorPara(this);

    switch (para) {
        case MirrorDialog::HORANDVER:
            imageEdit = li::mirror(imageOri, true, true);
            break;
        case MirrorDialog::HORIZONTAL:
            imageEdit = li::mirror(imageOri, true, false);
            break;
        case MirrorDialog::VERTICAL:
            imageEdit = li::mirror(imageOri, false, true);
            break;
        case MirrorDialog::NONE:
            break;
        default:
            break;
    }

    QImage ime = CvtToQImage(imageEdit);

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionRotate_triggered() {
    int para = RotateDialog::getRotatePara(this);

    imageEdit = li::rotate(imageOri, double(para));

    QImage ime = CvtToQImage(imageEdit);

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionScale_triggered() {
    long para = ScaleDialog::getScalePara(this, imageOri.width, imageOri.height);
    int _w = (int) ((para >> 32) & 0xFFFFFFFF);
    int _h = (int) (para & 0xFFFFFFFF);

    imageEdit = li::scale(imageOri, _w, _h);

    QImage ime = CvtToQImage(imageEdit);

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}