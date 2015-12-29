//
// Created by xin on 11/21/15.
//

#include "../include/scaledialog.h"
#include "ui_scaledialog.h"

ScaleDialog::ScaleDialog(QWidget *parent, int _w, int _h) : QDialog(parent), ui(new Ui::ScaleDialog),
                                                            width(_w), height(_h), fixRate(false),
                                                            oriWidth(_w), oriHeight(_h) {
    ui->setupUi(this);

    ui->spinBoxWidthAb->setMaximum(_w * 10);
    ui->spinBoxWidthAb->setValue(_w);
    ui->spinBoxHeightAb->setMaximum(_h * 10);
    ui->spinBoxHeightAb->setValue(_h);

    connect(ui->checkBoxFixRate, SIGNAL(stateChanged(int)), this, SLOT(setFixRate(int)));
    connect(ui->spinBoxWidthAb, SIGNAL(valueChanged(int)), this, SLOT(setWidthAb(int)));
    connect(ui->spinBoxHeightAb, SIGNAL(valueChanged(int)), this, SLOT(setHeightAb(int)));
}

ScaleDialog::~ScaleDialog() {
    delete ui;
}

void ScaleDialog::setFixRate(int state) {
    if (state == Qt::Checked) {
        fixRate = true;
    }
    else {
        fixRate = false;
    }
}

void ScaleDialog::setWidthAb(int _w) {
    if (fixRate) {
        width = _w;
        double fc = (double) _w / (double) oriWidth;
        height = (int) (oriHeight * fc);
        //ui->spinBoxHeightAb->setValue(height);
    }
    else {
        width = _w;
    }
}

void ScaleDialog::setHeightAb(int _h) {
    if (fixRate) {
        height = _h;
        double fc = (double) _h / (double) oriHeight;
        width = (int) (oriWidth * fc);
        //ui->spinBoxWidthAb->setValue(width);
    }
    else {
        width = _h;
    }
}

ScaleDialog::ScalePara ScaleDialog::getScalePara(QWidget *parent, int _w, int _h) {
    ScaleDialog dialog(parent, _w, _h);
    ScalePara res;

    if (dialog.exec() == QDialog::Accepted) {
        res.width = dialog.width;
        res.height = dialog.height;
        if (dialog.ui->radioButton_nearest->isChecked())
            dialog.type = 1;
        else
            dialog.type = 0;
        res.type = dialog.type;

        return res;
    }

    res.width = _w;
    res.width = _h;
    if (dialog.ui->radioButton_nearest->isChecked())
        dialog.type = 1;
    else
        dialog.type = 0;
    res.type = dialog.type;

    return res;
}

