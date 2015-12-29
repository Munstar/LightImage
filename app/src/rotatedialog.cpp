#include "../include/rotatedialog.h"
#include "ui_rotatedialog.h"


RotateDialog::RotateDialog(QWidget *parent) : QDialog(parent), ui(new Ui::RotateDialog), angle(0) {
    ui->setupUi(this);

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(setAngle(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setAngle(int)));
}


int RotateDialog::getRotatePara(QWidget *parent) {
    RotateDialog dialog(parent);

    if (dialog.exec() == QDialog::Accepted) {
        return dialog.angle;
    }
    return 0;
}

RotateDialog::~RotateDialog() {
    delete ui;
}

void RotateDialog::setAngle(int _angle) {
    angle = _angle;
}