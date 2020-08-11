#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>

class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = nullptr);
    float scaleSize;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    QPointF sceneMousePos;

signals:
    void mousemove_signal(QPointF point);
};

#endif // IMAGEVIEW_H
