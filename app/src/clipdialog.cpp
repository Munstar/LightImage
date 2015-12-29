#include "../include/clipdialog.h"
#include "ui_clipdialog.h"

ClipDialog::ClipDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ClipDialog), LTX(0), LTY(0), RBX(0), RBY(0) {
    ui->setupUi(this);

    connect(ui->spinBoxLTX, SIGNAL(valueChanged(int)), this, SLOT(setLTX(int)));
    connect(ui->spinBoxLTY, SIGNAL(valueChanged(int)), this, SLOT(setLTY(int)));
    connect(ui->spinBoxRBX, SIGNAL(valueChanged(int)), this, SLOT(setRBX(int)));
    connect(ui->spinBoxRBY, SIGNAL(valueChanged(int)), this, SLOT(setRBY(int)));
}

ClipDialog::~ClipDialog() {
    delete ui;
}

void ClipDialog::setLTX(int _x) {
    LTX = _x;
}

void ClipDialog::setLTY(int _y) {
    LTY = _y;
}

void ClipDialog::setRBX(int _x) {
    RBX = _x;
}

void ClipDialog::setRBY(int _y) {
    RBY = _y;
}

ClipDialog::ClipPara ClipDialog::getClipPara(QWidget *parent) {
    ClipDialog dialog(parent);
    ClipPara res;

    if (dialog.exec() == QDialog::Accepted) {
        res.LTX = dialog.LTX;
        res.LTY = dialog.LTY;
        res.RBX = dialog.RBX;
        res.RBY = dialog.RBY;

        return res;
    }

    res.LTY = 0;
    res.LTX = 0;
    res.RBY = 0;
    res.RBX = 0;

    return res;
}
