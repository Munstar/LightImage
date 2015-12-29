#ifndef LIGHTIMAGE_IMAGESCENE_H
#define LIGHTIMAGE_IMAGESCENE_H

#include <QGraphicsScene>

class ImageScene : public QGraphicsScene {
Q_OBJECT

public:
    explicit ImageScene(QObject *parent = 0);

    ~ImageScene();


signals:

    void sceneMouseMoved(int x, int y);


protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif //LIGHTIMAGE_IMAGESCENE_H
