#include "imageeditor.h"
#include "./ui_imageeditor.h"
#include "QDebug"
#include "imageview.h"
#include "QMessageBox"
#include "imageeffect.h"
#include "QFileDialog"

ImageEditor::ImageEditor(QFileInfo file)
    : QMainWindow()
    , ui(new Ui::ImageEditor)
    , img(ImageEffect(file))
{
    ui->setupUi(this);
    this->setAcceptDrops(false);
    ui->graphicsView->setAcceptDrops(false);
    ui->graphicsView->setScene(&scene);
    setWindowTitle(file.fileName());
    connect(ui->graphicsView, &ImageView::mousemove_signal,
            this,&ImageEditor::deal_mousemove_signal);
    if(img.getSrcImage() != NULL)
        showimage(img.getSrcImage());
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

void ImageEditor::showimage(QImage *image)
{
    //需在调用任何addItem（或addPixmap等）之前清除场景
    scene.clear();
    scene.addPixmap(QPixmap::fromImage(image->rgbSwapped()));
    nowImage = image;
}

void ImageEditor::deal_mousemove_signal(QPointF point)
{
    ui->statusBar->showMessage(QString::asprintf("x:%.0f y:%.0f",point.x(),point.y()));
}

void ImageEditor::on_boxblur_triggered()
{
    img.Blur(BoxBlur);
    showimage(img.getDstImage());
}

void ImageEditor::on_guassian_triggered()
{
    img.Blur(Gaussian);
    showimage(img.getDstImage());
}

void ImageEditor::on_saveimage_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
        "打开输入图像",
        QDir::currentPath(),
        "*.jpg;;*.png;;*.bmp");
    img.saveimage(nowImage,filename);
}
