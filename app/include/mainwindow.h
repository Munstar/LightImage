#ifndef LIGHTIMAGE_MAINWINDOW_H
#define LIGHTIMAGE_MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qgraphicsscene.h>
#include "LightImage.h"
#include "../include/imagescene.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionEdit_to_Origin_triggered();

    void on_actionRGB_to_Gray_triggered();

    void on_actionAdd_noise_triggered();

    void on_actionDCT_triggered();

    void on_actionFFT_triggered();

    void on_actionMirror_triggered();

    void on_actionRotate_triggered();

    void on_actionScale_triggered();

    void on_actionSmooth_triggered();

    void on_actionSharp_triggered();

    void on_actionMedian_triggered();

    void on_actionButterworth_LP_triggered();

    void on_actionButterworth_HP_triggered();

    void on_actionHistogram_Equ_triggered();

    void on_actionSearch_triggered();

    void on_actionMove_triggered();

    void on_actionClip_triggered();

    void updateStatusbar(int x, int y);



private:
    Ui::MainWindow *ui;
    li::Image imageOri;
    li::Image imageEdit;
    ImageScene *sceneOri;
    ImageScene *sceneEdit;

};


#endif //LIGHTIMAGE_MAINWINDOW_H
