//
// Created by xin on 11/17/15.
//

#include "../include/mainwindow.h"
#include "../include/mirrordialog.h"
#include "../include/rotatedialog.h"
#include "../include/scaledialog.h"
#include "ui_mainwindow.h"
#include "../include/util.hpp"
#include <complex>

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
    //li::imsave(imageOri, QString("/home/xin/Pictures/save_test.bmp").toStdString().c_str());

    //li::Matrix_<std::complex<float>> fmat = li::dft(imageOri);
    //imageEdit = li::renderPowerSpectrum(fmat);
    //imageEdit = li::idft(fmat, imageOri.width, imageOri.height);

    //li::Matrix_<float> cmat = li::dct(imageOri);
    //imageEdit = li::renderPowerSpectrum(cmat);
    //imageEdit = li::idct(cmat, imageOri.width, imageOri.height);

    //li::Filter_kernel k(-1.0/9.0, -1.0/9.0, -1.0/9.0,
    //-1.0/9.0, 17.0/9.0, -1.0/9.0,
    //-1.0/9.0, -1.0/9.0, -1.0/9.0);

    //imageEdit = li::base_filter(imageOri, k);

    //imageEdit = li::histogram_balance(imageOri);

    imageEdit = li::pepper_salt_noise(imageOri, (imageOri.height * imageOri.width) / 20);
    //imageEdit = li::median_filter(imageEdit);
    imageEdit = li::butterworth_filter(imageOri, 56, 2);


    li::Histogram *ho = new li::Histogram(imageOri);
    li::Image histOri = ho->Render(256, 180);
    li::Histogram *he = new li::Histogram(imageEdit);
    li::Image histEdit = he->Render(256, 180);

    QImage imho = CvtToQImage(histOri);
    QImage imhe = CvtToQImage(histEdit);
    QImage imo = CvtToQImage(imageOri);
    QImage ime = CvtToQImage(imageEdit);

    ui->labelHistOri->setPixmap(QPixmap::fromImage(imho));
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(imhe));

    sceneOri->clear();
    sceneOri->addPixmap(QPixmap::fromImage(imo));
    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
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

    imageEdit = li::scale_linear(imageOri, _w, _h);

    QImage ime = CvtToQImage(imageEdit);

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}