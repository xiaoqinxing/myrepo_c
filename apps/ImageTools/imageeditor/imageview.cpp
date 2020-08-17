#include "imageview.h"
#include "QMouseEvent"
#include "QDebug"
ImageView::ImageView(QWidget *parent) : QGraphicsView(parent)
{
    scaleSize = 1.0;
//    isCtrlKeyPressed = false;
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
        //转换到scene坐标
        sceneMousePos = mapToScene(event->pos());
        emit mousemove_signal(sceneMousePos);
        //加上这句话就可以在原有的处理之上增加自己的处理！！！
        QGraphicsView::mouseMoveEvent(event);
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
    event->ignore();
}

//void ImageView::keyPressEvent(QKeyEvent *event)
//{
//    if(event->modifiers() == Qt::ControlModifier){
//        isCtrlKeyPressed = true;
////        this->setOverrideCursor(Qt::OpenHandCursor); //设置鼠标样式
//    }
//}
//void ImageView::keyReleaseEvent(QKeyEvent *event)
//{
//        isCtrlKeyPressed = false;
////        setOverrideCursor(Qt::ArrowCursor); //改回鼠标样式
//}
