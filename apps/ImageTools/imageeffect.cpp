#include "imageeffect.h"
#include "QMessageBox"
#include "QObject"
#include "QString"
using namespace cv;
ImageEffect::ImageEffect(QFileInfo file)
{
    srcimage = imread(file.absoluteFilePath().toStdString());
    if(srcimage.data != NULL)
    {
        /*需要重点注意的是，当以这种方式传递数据时，就像我们在将Mat转换成
         * QImage时看到的那样，其实质是在Qt和OpenCV的类之间传递了相同的内存空间。
         * 这意味着，如果修改前一例子中的Mat类，实际上就是修改了图像类，因为你刚刚将
         * 其数据指针传递给了Mat类。这两种方法都是非常有用的（更易于图像处理）同时也
         * 是非常危险的（可能造成应用程序的崩溃）
         */
        srcqimage = new QImage(srcimage.data,
                               srcimage.cols,
                               srcimage.rows,
                               srcimage.step,
                               QImage::Format_BGR888);
        dstimage = srcimage.clone();
        dstqimage = new QImage(dstimage.data,
                               dstimage.cols,
                               dstimage.rows,
                               dstimage.step,
                               QImage::Format_BGR888);
    }
    else
    {
        srcqimage = nullptr;
        dstqimage = nullptr;
    }
}

ImageEffect::~ImageEffect()
{
    delete srcqimage;
    delete dstqimage;
}

void ImageEffect::saveimage(QImage* image, QString filename)
{
    if(image == srcqimage)
        imwrite(filename.toStdString(), srcimage);
    else if(image == dstqimage)
        imwrite(filename.toStdString(), dstimage);
}

QImage* ImageEffect::getSrcImage()
{
    return srcqimage;
}
QImage* ImageEffect::getDstImage()
{
    return dstqimage;
}

void ImageEffect::Blur(typeBlur type)
{
    switch (type) {
        case BoxBlur:
            boxFilter(srcimage,dstimage,-1,Size(3,3));
            break;
        case Gaussian:
            GaussianBlur(srcimage,dstimage,Size(5,5),0,0);
    }
}


