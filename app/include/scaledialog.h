#ifndef LIGHTIMAGE_SCALEDIALOG_H
#define LIGHTIMAGE_SCALEDIALOG_H

#include <QDialog>

namespace Ui {
    class ScaleDialog;
}

class ScaleDialog : public QDialog {
Q_OBJECT

public:
    typedef struct _ScalePara {
        int width;
        int height;
        int type;
    } ScalePara;

public:
    explicit ScaleDialog(QWidget *parent, int _w, int _h);

    ~ScaleDialog();

    static ScalePara getScalePara(QWidget *parent, int _w, int _h);

private slots:

    void setFixRate(int state);

    void setWidthAb(int _w);

    void setHeightAb(int _h);

private:
    Ui::ScaleDialog *ui;

    int oriWidth;
    int oriHeight;
    int width;
    int height;
    int type;
    bool fixRate;

};


#endif //LIGHTIMAGE_SCALEDIALOG_H
