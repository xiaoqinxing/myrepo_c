#ifndef IMAGES_H
#define IMAGES_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "QFileInfo"
#include "imageeffect.h"
#include "staticsview.h"
//#include "histview.h"
#include "histgramview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ImageEditor; }
QT_END_NAMESPACE
class ImageEditor : public QMainWindow
{
    Q_OBJECT

public:
//    ImageEditor(QWidget *parent = nullptr);
    ImageEditor(QString &filename);
    ~ImageEditor();

private:
    Ui::ImageEditor *ui;
    ImageEffect img;
    QGraphicsScene scene;
    QPixmap pixmap;
    QPointF scensMousePos;
    QImage *nowImage;
    StaticsView staticsview;
    void showimage(QImage *img);
    void deal_mousemove_signal(QPointF point);
    int rect_x1,rect_y1,rect_x2,rect_y2;
//    QCustomPlot histplot;
//    HistView hist;
    HistgramView hist;

protected:

private slots:
    void on_saveimage_triggered();
    void on_guassian_triggered();
    void on_boxblur_triggered();
    void on_medianblur_triggered();
    void on_bilateralblur_triggered();
    void on_actioncompare_triggered();
    void on_statics_toggled(bool arg1);
    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);
    void on_historgram_triggered();
};
#endif // IMAGES_H
