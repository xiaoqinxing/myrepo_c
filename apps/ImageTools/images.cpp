#include "images.h"
#include "./ui_images.h"
#include "QGraphicsView"
#include "QDragEnterEvent"
#include "QScrollBar"
#include "QDropEvent"
#include "QMimeData"
#include "QDebug"
#include "QWheelEvent"
#include "QtMath"
#include "QMainWindow"
#include "string"

Images::Images(QFileInfo file)
    : QMainWindow()
    , ui(new Ui::Images)
{
    ui->setupUi(this);
    this->setAcceptDrops(false);
    ui->graphicsView->setAcceptDrops(false);
    ui->graphicsView->setScene(&scene);
    setWindowTitle(file.fileName());
    /*需要重点注意的是，当以这种方式传递数据时，就像我们在将Mat转换成
     * QImage时看到的那样，其实质是在Qt和OpenCV的类之间传递了相同的内存空间。
     * 这意味着，如果修改前一例子中的Mat类，实际上就是修改了图像类，因为你刚刚将
     * 其数据指针传递给了Mat类。这两种方法都是非常有用的（更易于图像处理）同时也
     * 是非常危险的（可能造成应用程序的崩溃）
     */
    image = cv::imread(file.absoluteFilePath().toStdString());
    if(image.data != NULL)
        showimage(image);
    else
        QMessageBox::critical(this,
                           tr("错误"),
                           tr("图像打不开"));
}

Images::~Images()
{
    qDebug() << "delete images";
    delete ui;
}

void Images::showimage(cv::Mat &mat)
{
    QImage qimage(mat.data,
                 mat.cols,
                 mat.rows,
                 mat.step,
                 QImage::Format_BGR888);
    //需在调用任何addItem（或addPixmap等）之前清除场景
    scene.clear();
    scene.addPixmap(QPixmap::fromImage(qimage.rgbSwapped()));
}
void Images::wheelEvent(QWheelEvent *event)
{
    qDebug()<< event->orientation();
    if(event->orientation()== Qt::Vertical)
    {
        double angleDeltaY =event->angleDelta().y();
        double zoomFactor = qPow(1.0015,angleDeltaY);
        ui->graphicsView->scale(zoomFactor,zoomFactor);
        if(angleDeltaY>0)
        {

            scensMousePos = ui->graphicsView->mapToScene(event->pos());
            ui->graphicsView->centerOn(scensMousePos);
        }
        qDebug()<< scensMousePos;
        ui->graphicsView->viewport()->update();
        event->ignore();
    }
    else{
        event->ignore();
    }
}
void Images::mouseMoveEvent(QMouseEvent *event)
{
    scensMousePos = ui->graphicsView->mapToScene(event->pos());
    qDebug()<< scensMousePos;
    QString pos_status;
    pos_status = "x: "+ QString::number(scensMousePos.x()) +" y: "+ QString::number(scensMousePos.y());
    ui->statusBar->showMessage(pos_status);
}
