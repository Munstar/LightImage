#ifndef LIGHTIMAGE_ROTATEDIALOG_H
#define LIGHTIMAGE_ROTATEDIALOG_H

#include <QDialog>

namespace Ui {
    class RotateDialog;
}

class RotateDialog : public QDialog {
Q_OBJECT

public:
    explicit RotateDialog(QWidget *parent);

    ~RotateDialog();

    static int getRotatePara(QWidget *);

private slots:

    void setAngle(int _angle);

private:
    Ui::RotateDialog *ui;
    int angle;
};

#endif //LIGHTIMAGE_ROTATEDIALOG_H
