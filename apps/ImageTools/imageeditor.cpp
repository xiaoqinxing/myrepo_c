#include "imageeditor.h"
#include "./ui_imageeditor.h"
#include "QDebug"
#include "imageview.h"
#include "QMessageBox"

ImageEditor::ImageEditor(QFileInfo file)
    : QMainWindow()
    , ui(new Ui::ImageEditor)
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
    connect(ui->graphicsView, &ImageView::mousemove_signal,
            this,&ImageEditor::deal_mousemove_signal);
    image = cv::imread(file.absoluteFilePath().toStdString());
    if(image.data != NULL)
        showimage(image);
    else
        QMessageBox::critical(this,
                           tr("错误"),
                           tr("图像打不开"));
}

ImageEditor::~ImageEditor()
{
    qDebug() << "delete images";
    delete ui;
}

void ImageEditor::showimage(cv::Mat &mat)
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



void ImageEditor::deal_mousemove_signal(QPointF point)
{
    ui->statusBar->showMessage(QString::asprintf("x:%.0f y:%.0f",point.x(),point.y()));
}
