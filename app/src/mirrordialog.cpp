//
// Created by xin on 11/20/15.
//

#include "../include/mirrordialog.h"
#include "ui_mirrordialog.h"

MirrorDialog::MirrorDialog(QWidget *parent) : QDialog(parent), ui(new Ui::MirrorDialog),
                                              horizontal(false), vertical(false) {
    ui->setupUi(this);
    connect(ui->checkBoxHor, SIGNAL(stateChanged(int)), this, SLOT(setHorizontal(int)));
    connect(ui->checkBoxVer, SIGNAL(stateChanged(int)), this, SLOT(setVertical(int)));
}

MirrorDialog::~MirrorDialog() {
    delete ui;
}

void MirrorDialog::setHorizontal(int state) {
    horizontal = (state == Qt::Checked);
}

void MirrorDialog::setVertical(int state) {
    vertical = (state == Qt::Checked);
}

int MirrorDialog::getMirrorPara(QWidget *parent) {
    MirrorDialog dialog(parent);

    if (dialog.exec() == QDialog::Accepted) {
        if (dialog.horizontal && dialog.vertical) {
            return HORANDVER;
        }
        else if (dialog.horizontal) {
            return HORIZONTAL;
        }
        else if (dialog.vertical) {
            return VERTICAL;
        } else {
            return NONE;
        }
    }

    return NONE;
}

