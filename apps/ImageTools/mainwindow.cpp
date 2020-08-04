#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QGraphicsRectItem"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QMimeData"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QGraphicsRectItem *item = new QGraphicsRectItem(0,0,100,100);
//    item->setAcceptDrops(true);
//    item->setAcceptHoverEvents(true);
//    item->setAcceptedMouseButtons(
//                Qt::LeftButton |
//                Qt::RightButton|
//                Qt::MidButton);
    this->setAcceptDrops(true);
    ui->graphicsView->setAcceptDrops(false);
    ui->graphicsView->setScene(&scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    QString acceptedFileTypes;
    acceptedFileTypes.append("jpg");
    acceptedFileTypes.append("png");
    acceptedFileTypes.append("bmp");
    if(event->mimeData()->hasUrls() &&
       event->mimeData()->urls().count() == 1){
        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        //check file is not cunzai
        if(acceptedFileTypes.contains(file.suffix().toLower())){
            event->acceptProposedAction();
        }
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
    if(pixmap.load(file.absoluteFilePath()))
    {
//        ui->label->setPixmap(pixmap.scaled(ui->label->size(),
//                                           Qt::KeepAspectRatio,
//                                           Qt::SmoothTransformation));
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
Q_UNUSED(event);
    if(!pixmap.isNull())
    {
        ui->label->setPixmap(pixmap.scaled(ui->label->width()-5,
                                           ui->label->height()-5,
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation));
    }
}
