//
// Created by xin on 12/29/15.
//

#include "../include/movedialog.h"
#include "ui_movedialog.h"

MoveDialog::MoveDialog(QWidget *parent) : QDialog(parent), ui(new Ui::MoveDialog), X(0), Y(0) {
    ui->setupUi(this);

    connect(ui->spinBoxX, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
    connect(ui->spinBoxY, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));

}

MoveDialog::~MoveDialog() {
    delete(ui);
}

void MoveDialog::setX(int _x) {
    X = _x;
}

void MoveDialog::setY(int _y) {
    Y = _y;
}

MoveDialog::MovePara MoveDialog::getMovePara(QWidget *parent) {
    MoveDialog dialog(parent);
    MovePara res;

    if (dialog.exec() == QDialog::Accepted) {
        res.x = dialog.X;
        res.y = dialog.Y;
        return res;
    }

    res.x = 0;
    res.y = 0;

    return res;
}

