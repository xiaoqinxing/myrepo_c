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

//    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    ui->graphicsView->horizontalScrollBar()->blockSignals(true);
//    ui->graphicsView->verticalScrollBar()->blockSignals(true);

    if(pixmap.load(file.absoluteFilePath()))
    {
        //需在调用任何addItem（或addPixmap等）之前清楚场景
        scene.clear();
        scene.addPixmap(pixmap);
    }
    else
    {
        QMessageBox::critical(this,
                           tr("错误"),
                           tr("图像打不开"));
    }
}

Images::~Images()
{
    qDebug() << "delete images";
    delete ui;
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

