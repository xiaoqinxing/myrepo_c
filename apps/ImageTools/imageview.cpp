#include "imageview.h"
#include "QMouseEvent"
#include "QDebug"
ImageView::ImageView(QWidget *parent) : QGraphicsView(parent)
{
    scaleSize = 1.0;
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    //转换到scene坐标
    sceneMousePos = mapToScene(event->pos());
    emit mousemove_signal(sceneMousePos);
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    qDebug()<< event->angleDelta();
    double angleDeltaY =event->angleDelta().y();
    //以鼠标位置为中心
    centerOn(sceneMousePos);
    if(angleDeltaY>0)
    {
        scale(1.2,1.2);
        scaleSize *= 1.2;
    }
    else
    {
        scale(1.0/1.2,1.0/1.2);
        scaleSize /= 1.2;
    }
    viewport()->update();
    event->accept();
}
