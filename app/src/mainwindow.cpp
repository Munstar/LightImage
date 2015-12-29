#include "../include/mainwindow.h"
#include "../include/mirrordialog.h"
#include "../include/rotatedialog.h"
#include "../include/scaledialog.h"
#include "../include/movedialog.h"
#include "../include/clipdialog.h"
#include "ui_mainwindow.h"
#include "../include/util.hpp"

#include <QFileDialog>
#include <app/include/movedialog.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    sceneOri = new ImageScene();
    sceneEdit = new ImageScene();

    ui->graphicsViewOri->setScene(sceneOri);
    ui->graphicsViewEdit->setScene(sceneEdit);

    connect(sceneOri, SIGNAL(sceneMouseMoved(int, int)), this, SLOT(updateStatusbar(int, int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/xin/Pictures", tr("Images (*.bmp)"));
    if (filename.isEmpty())
        return;
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

    //imageEdit = li::pepper_salt_noise(imageOri, (imageOri.height * imageOri.width) / 20);
    //imageEdit = li::median_filter(imageEdit);
    //imageEdit = li::butterworth_filter(imageOri, 56, 2);


    li::Histogram *ho = new li::Histogram(imageOri);
    li::Image histOri = ho->Render(256, 180);
    //li::Histogram *he = new li::Histogram(imageEdit);
    //li::Image histEdit = he->Render(256, 180);

    QImage imho = CvtToQImage(histOri);
    //QImage imhe = CvtToQImage(histEdit);
    QImage imo = CvtToQImage(imageOri);
    //QImage ime = CvtToQImage(imageEdit);

    ui->labelHistOri->setPixmap(QPixmap::fromImage(imho));
    //ui->labelHistEdit->setPixmap(QPixmap::fromImage(imhe));

    sceneOri->clear();
    sceneOri->addPixmap(QPixmap::fromImage(imo));
    //sceneEdit->clear();
    //sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionSave_triggered() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Open File"), "/home/xin/Pictures", tr("Images (*.bmp)"));
    if (filename.isEmpty())
        return;
    if (imageEdit.width == 0)
        return;
    li::imsave(imageEdit, filename.toStdString().c_str());
}

void MainWindow::on_actionEdit_to_Origin_triggered() {
    imageOri = imageEdit.copyto();
    li::Histogram ho(imageOri);
    li::Image histOri = ho.Render(256, 180);

    QImage imo = CvtToQImage(imageOri);
    QImage iho = CvtToQImage(histOri);
    ui->labelHistOri->setPixmap(QPixmap::fromImage(iho));

    sceneOri->clear();
    sceneOri->addPixmap(QPixmap::fromImage(imo));
}

void MainWindow::on_actionRGB_to_Gray_triggered() {
    if (imageOri.channels != 1) {
        imageEdit = li::rgb2gray(imageOri);
        QImage ime = CvtToQImage(imageEdit);
        li::Histogram he(imageEdit);
        li::Image histEdit = he.Render(256, 180);
        QImage ihe = CvtToQImage(histEdit);
        ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

        sceneEdit->clear();
        sceneEdit->addPixmap(QPixmap::fromImage(ime));
    }
}

void MainWindow::on_actionFFT_triggered() {
    li::Image temp = li::rgb2gray(imageOri);
    li::Matrix_<std::complex<float>> fmat = li::dft(temp);
    imageEdit = li::renderPowerSpectrum(fmat);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    QImage ime = CvtToQImage(imageEdit);

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionSharp_triggered() {
    li::Image temp = li::rgb2gray(imageOri);

    imageEdit = li::sharp(temp);
    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::updateStatusbar(int x, int y) {
    QString m;
    m += "X: ";
    m += QString::number(x);
    m += ", Y: ";
    m += QString::number(y);
    if (x < imageOri.width && y < imageOri.height && x >= 0 && y >= 0) {
        if (imageOri.channels == 1) {
            m += "; V: ";
            m += QString::number(imageOri.data[y * imageOri.width + x]);
        } else {
            m += "; R: ";
            m += QString::number(imageOri.data[(y * imageOri.width + x) * imageOri.channels]);
            m += ", G: ";
            m += QString::number(imageOri.data[(y * imageOri.width + x) * imageOri.channels + 1]);
            m += ", B: ";
            m += QString::number(imageOri.data[(y * imageOri.width + x) * imageOri.channels + 2]);
        }
    }
    ui->statusbar->showMessage(m, 0);
}

void MainWindow::on_actionHistogram_Equ_triggered() {
    li::Image temp = li::rgb2gray(imageOri);

    imageEdit = li::histogram_eq(temp);
    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

bool pair_grater_than(QPair<QString, double> p1, QPair<QString, double> p2) {
    if (p1.second > p2.second)
        return true;
    else
        return false;
}

void MainWindow::on_actionSearch_triggered() {
    QString pathname = QFileDialog::getExistingDirectory(this, tr("Search Directory"), "/home",
                                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (pathname.isEmpty())
        return;

    QDir dir(pathname);

    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);

    QList<QPair<QString, double >> simiList;

    for (int i = 0; i != fileList.size(); ++i) {
        QString filename = fileList.at(i).absoluteFilePath();
        li::Image temp = li::imload(filename.toStdString().c_str());
        double simifactor = li::hist_simi(imageOri, temp);
        simiList.insert(i, QPair<QString, double>(filename, simifactor));
    }

    qSort(simiList.begin(), simiList.end(), pair_grater_than);

    std::cout << "Similarity Rank:" << std::endl;
    for (int j = 0; j < simiList.size(); ++j) {
        std::cout << simiList.at(j).first.toStdString() << ", " << simiList.at(j).second << std::endl;
    }

    imageEdit = li::imload(simiList.at(0).first.toStdString().c_str());

    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionSmooth_triggered() {
    li::Image temp = li::rgb2gray(imageOri);

    imageEdit = li::smooth(temp);
    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionMedian_triggered() {
    li::Image temp = li::rgb2gray(imageOri);

    imageEdit = li::median_filter(temp);
    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionButterworth_HP_triggered() {
    li::Image temp = li::rgb2gray(imageOri);

    imageEdit = li::butterworth_filter(temp, 56, -2);
    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionButterworth_LP_triggered() {
    li::Image temp = li::rgb2gray(imageOri);

    imageEdit = li::butterworth_filter(temp, 56, 2);
    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionDCT_triggered() {
    li::Image temp = li::rgb2gray(imageOri);
    li::Matrix_<float> cmat = li::dct(temp);
    imageEdit = li::renderPowerSpectrum(cmat);
    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionAdd_noise_triggered() {
    if (imageOri.channels != 1)
        return;
    imageEdit = li::pepper_salt_noise(imageOri, (imageOri.height * imageOri.width) / 20);

    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

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

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionRotate_triggered() {
    int para = RotateDialog::getRotatePara(this);

    imageEdit = li::rotate(imageOri, double(para));

    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionScale_triggered() {
    ScaleDialog::ScalePara para;

    para = ScaleDialog::getScalePara(this, imageOri.width, imageOri.height);

    if (para.type == 1)
        imageEdit = li::scale_nearest(imageOri, para.width, para.height);
    else
        imageEdit = li::scale_linear(imageOri, para.width, para.height);

    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionMove_triggered() {
    MoveDialog::MovePara para;

    para = MoveDialog::getMovePara(this);

    if (para.x == 0 && para.y == 0)
        return;
    imageEdit = li::move(imageOri, para.x, para.y);

    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}

void MainWindow::on_actionClip_triggered() {
    ClipDialog::ClipPara para;

    para = ClipDialog::getClipPara(this);

    if (para.LTX == para.RBX || para.LTY == para.RBY)
        return;
    if (para.LTX < 0 || para.LTY < 0 || para.RBX < 0 || para.RBY < 0)
        return;
    if (para.LTX > imageOri.width || para.LTY > imageOri.height || para.RBX > imageOri.width ||
        para.RBY > imageOri.height)
        return;

    imageEdit = li::clip(imageOri, para.LTX, para.LTY, para.RBX, para.RBY);

    QImage ime = CvtToQImage(imageEdit);

    li::Histogram he(imageEdit);
    li::Image histEdit = he.Render(256, 180);
    QImage ihe = CvtToQImage(histEdit);
    ui->labelHistEdit->setPixmap(QPixmap::fromImage(ihe));

    sceneEdit->clear();
    sceneEdit->addPixmap(QPixmap::fromImage(ime));
}