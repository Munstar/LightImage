//
// Created by xin on 11/20/15.
//

#ifndef LIGHTIMAGE_MIRRORDIALOG_H
#define LIGHTIMAGE_MIRRORDIALOG_H

#include <QDialog>

namespace Ui {
    class MirrorDialog;
}

class MirrorDialog : public QDialog {
Q_OBJECT

public:
    explicit MirrorDialog(QWidget *parent);

    ~MirrorDialog();

    static int getMirrorPara(QWidget *parent);

    static const int NONE = 0;
    static const int HORIZONTAL = 1;
    static const int VERTICAL = 2;
    static const int HORANDVER = 3;

private slots:

    void setHorizontal(int state);

    void setVertical(int state);

private:
    Ui::MirrorDialog *ui;
    bool horizontal;
    bool vertical;

};


#endif //LIGHTIMAGE_MIRRORDIALOG_H
