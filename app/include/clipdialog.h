#ifndef LIGHTIMAGE_CLIPDIALOG_H
#define LIGHTIMAGE_CLIPDIALOG_H


#include <QDialog>

namespace Ui {
    class ClipDialog;
}

class ClipDialog : public QDialog {
Q_OBJECT

public:
    typedef struct _ClipPara {
        int LTX;
        int LTY;
        int RBX;
        int RBY;
    } ClipPara;

public:
    explicit ClipDialog(QWidget *parent);

    ~ClipDialog();

    static ClipPara getClipPara(QWidget *parent);

private slots:

    void setLTX(int _x);

    void setLTY(int _y);

    void setRBX(int _x);

    void setRBY(int _y);

private:
    Ui::ClipDialog *ui;
    int LTX;
    int LTY;
    int RBX;
    int RBY;
};


#endif //LIGHTIMAGE_CLIPDIALOG_H
