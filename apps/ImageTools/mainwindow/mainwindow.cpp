#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageeditor.h"
#include "QMimeData"
#include "QDragEnterEvent"
#include "QDebug"
#include "QDir"
#include "QFileDialog"
#include "SimplePlayer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rtspconfigView()
    ,player()
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    connect(&rtspconfigView,&RtspConfigView::rtspconfig_signal,this,&MainWindow::deal_video_start_signal);
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
    //打开文件的时候，需要记住上一次打开的路径！
    QSettings settings("config", "ImageTool", this);
    QString filename = QFileDialog::getOpenFileName(this,
        "打开输入图像",
        settings.value("LastFilePath",QDir::currentPath()).toString(),
        "Images (*.jpg *.png *.bmp)");
    if (QFile::exists(filename)) {
        ImageEditor *a = new ImageEditor(filename);
        int i = filename.lastIndexOf('/');
        QString Path = filename.left(i);
        settings.setValue("LastFilePath", Path);
        ui->mdiArea->addSubWindow(a);
        a->show();
    }
}

void MainWindow::on_actionda_2_triggered()
{
    rtspconfigView.show();
}
void MainWindow::deal_video_start_signal(QString url)
{
//    videoplayer *a = new videoplayer();
    player.setSrcName(url);
    ui->mdiArea->addSubWindow(&player);
    player.show();
//        SimplePlayer *a = new SimplePlayer();
//        ui->mdiArea->addSubWindow(a);
//        a->show();
}
