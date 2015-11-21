//
// Created by xin on 11/17/15.
//

#ifndef LIGHTIMAGE_MAINWINDOW_H
#define LIGHTIMAGE_MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qgraphicsscene.h>
#include "LightImage.h"

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

    void on_actionMirror_triggered();

    void on_actionRotate_triggered();

    void on_actionScale_triggered();


private:
    Ui::MainWindow *ui;
    li::Image imageOri;
    li::Image imageEdit;
    QGraphicsScene *sceneOri;
    QGraphicsScene *sceneEdit;

};


#endif //LIGHTIMAGE_MAINWINDOW_H
