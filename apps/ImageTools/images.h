#ifndef IMAGES_H
#define IMAGES_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "QFileInfo"
#include "QDragEnterEvent"
#include "QMessageBox"
#include "QDrag"
#include "QFile"
#include "opencv2/opencv.hpp"
QT_BEGIN_NAMESPACE
namespace Ui { class Images; }
QT_END_NAMESPACE

class Images : public QMainWindow
{
    Q_OBJECT

public:
//    Images(QWidget *parent = nullptr);
    Images(QFileInfo file);
    ~Images();

private:
    Ui::Images *ui;
    QGraphicsScene scene;
    QPixmap pixmap;
    QPointF scensMousePos;
    cv::Mat image;
    void showimage(cv::Mat &mat);
    void deal_mousemove_signal(QPointF point);

protected:

};
#endif // IMAGES_H
