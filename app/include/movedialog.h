#ifndef LIGHTIMAGE_MOVEDIALOG_H
#define LIGHTIMAGE_MOVEDIALOG_H

#include <QDialog>

namespace Ui {
    class MoveDialog;
}

class MoveDialog : public QDialog {
Q_OBJECT

public:
    typedef struct {
        int x;
        int y;
    } MovePara;

public:
    explicit MoveDialog(QWidget *parent);

    ~MoveDialog();

    static MovePara getMovePara(QWidget *);

private slots:

    void setX(int _x);

    void setY(int _y);

private:
    Ui::MoveDialog *ui;
    int X;
    int Y;
};


#endif //LIGHTIMAGE_MOVEDIALOG_H
