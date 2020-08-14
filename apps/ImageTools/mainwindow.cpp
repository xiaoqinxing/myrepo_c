#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageeditor.h"
#include "QMimeData"
#include "QDragEnterEvent"
#include "QDebug"
#include "QDir"
#include "QFileDialog"

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
    QString filename = file.absoluteFilePath();
    ImageEditor *a = new ImageEditor(filename);
    ui->mdiArea->addSubWindow(a);
    a->show();
}


void MainWindow::on_actionda_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "打开输入图像",
        QDir::currentPath(),
        "Images (*.jpg *.png *.bmp)");
    if (QFile::exists(filename)) {
        ImageEditor *a = new ImageEditor(filename);
        ui->mdiArea->addSubWindow(a);
        a->show();
    }
}
