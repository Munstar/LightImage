//
// Created by xin on 12/28/15.
//

#include "../include/imagescene.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>

ImageScene::ImageScene(QObject *parent) : QGraphicsScene(parent) {

}

ImageScene::~ImageScene() { }

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    emit sceneMouseMoved((int) event->scenePos().x(), (int) event->scenePos().y());
    QGraphicsScene::mouseMoveEvent(event);
}
