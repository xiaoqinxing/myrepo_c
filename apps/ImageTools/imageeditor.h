#ifndef IMAGES_H
#define IMAGES_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "opencv2/opencv.hpp"
#include "QFileInfo"
QT_BEGIN_NAMESPACE
namespace Ui { class ImageEditor; }
QT_END_NAMESPACE

class ImageEditor : public QMainWindow
{
    Q_OBJECT

public:
//    ImageEditor(QWidget *parent = nullptr);
    ImageEditor(QFileInfo file);
    ~ImageEditor();

private:
    Ui::ImageEditor *ui;
    QGraphicsScene scene;
    QPixmap pixmap;
    QPointF scensMousePos;
    cv::Mat image;
    void showimage(cv::Mat &mat);
    void deal_mousemove_signal(QPointF point);

protected:

};
#endif // IMAGES_H
