#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QCloseEvent"
#include "QSettings"
#include "opencv2/opencv.hpp"
#include "qdir.h"
#include "qfile.h"
#include "qfiledialog.h"
#include "qmessagebox.h"

Images::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "打开输入图像",
        QDir::currentPath(),
        "Images (*.jpg *.png *.bmp)");
    if (QFile::exists(filename)) {
        ui->lineEdit->setText(filename);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
        "打开输入图像",
        QDir::currentPath(),
        "*.jpg;;*.png;;*.bmp");
    if (!filename.isEmpty()) {
        ui->outputLineEdit->setText(filename);
        using namespace cv;
        Mat inputImg, outImg;
        inputImg = imread(ui->lineEdit->text().toStdString());
        if (ui->medianBlurRadioButton->isChecked())
            cv::medianBlur(inputImg, outImg, 5);
        else if (ui->guassianblurradiobutton->isChecked())
            cv::GaussianBlur(inputImg, outImg, Size(5, 5), 1.25);
        imwrite(filename.toStdString(), outImg);
        if (ui->displayimagecheckbox->isChecked())
            imshow("output image", outImg);
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    int ret = QMessageBox::warning(this,
        "退出",
        "是否确定关闭程序？",
        QMessageBox::Yes,
        QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        saveSettings();
        event->accept();
    } else
        event->ignore();
}
/**
 * @brief 加载上一次关闭的参数设置状态
 */
void MainWindow::loadSettings()
{
    QSettings settings("packt", "opencv_qt_test", this);
    ui->lineEdit->setText(settings.value("inputLineEdit", "").toString());
    ui->outputLineEdit->setText(settings.value("outputLineEdit", "").toString());
    ui->medianBlurRadioButton->setChecked(settings.value("mediaBlurRadioButton", false).toBool());
    ui->guassianblurradiobutton->setChecked(settings.value("guassianBlurRadioButton", false).toBool());
    ui->displayimagecheckbox->setChecked(settings.value("displayImageCheckBox", false).toBool());
}
/**
 * @brief 保存参数设置状态
 */
void MainWindow::saveSettings()
{
    QSettings settings("packt", "opencv_qt_test", this);
    settings.setValue("inputLineEdit", ui->lineEdit->text());
    settings.setValue("outputLineEdit", ui->outputLineEdit->text());
    settings.setValue("mediaBlurRadioButton", ui->medianBlurRadioButton->text());
    settings.setValue("guassianBlurRadioButton", ui->guassianblurradiobutton->text());
    settings.setValue("displayImageCheckBox", ui->displayimagecheckbox->text());
}
