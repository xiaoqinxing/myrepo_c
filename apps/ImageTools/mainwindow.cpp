#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "images.h"
#include "QGraphicsRectItem"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QMimeData"
#include "QDebug"
#include "QWheelEvent"
#include "QtMath"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
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
    Images *a = new Images(file);
//    ui->gridLayout->addWidget(a);
    ui->mdiArea->addSubWindow(a);
    a->show();
}

