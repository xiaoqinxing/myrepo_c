#include "imageeffect.h"
#include "QMessageBox"
#include "QObject"
#include "QString"
#include "QDebug"
using namespace cv;
ImageEffect::ImageEffect(QString &filename)
{
    //需要加toLocal8Bit()，将字符串转成unicode，才能打开中文路径，否则imread会出bug!!
    srcimage = imread(filename.toLocal8Bit().toStdString());
    //opencv默认格式是BGR的，转成RGB
    cvtColor(srcimage,srcimage,COLOR_BGR2RGB);
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
                               QImage::Format_RGB888);
        dstimage = srcimage.clone();
        dstqimage = new QImage(dstimage.data,
                               dstimage.cols,
                               dstimage.rows,
                               dstimage.step,
                               QImage::Format_RGB888);
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
    imageconvert(image);
    imwrite(filename.toStdString(), nowimage);
}

//convert from QImage to Mat
void ImageEffect::imageconvert(QImage *image)
{
    if(image == srcqimage){
        nowimage = srcimage;
    }
    else if(image == dstqimage){
        nowimage = dstimage;
    }
}

tRgbColor ImageEffect::getImagePoint(QImage *image, int x, int y)
{
    Vec3b point_rgb;
    tRgbColor ret;
    imageconvert(image);
    //at函数中i对应的是点的y坐标，j对应的是点的x坐标，而不是我们习惯的（x,y）
    point_rgb = srcimage.at<Vec3b>(y,x);
    ret.R = point_rgb[0];
    ret.G = point_rgb[1];
    ret.B = point_rgb[2];
    return ret;
}

QImage* ImageEffect::getSrcImage()
{
    return srcqimage;
}

QImage* ImageEffect::getDstImage()
{
    return dstqimage;
}

#define BLUR_LEN 5
#define BLUR_SIZE Size(BLUR_LEN,BLUR_LEN)
void ImageEffect::Blur(typeBlur type)
{
    switch (type) {
        case BoxBlur:
            boxFilter(srcimage,dstimage,-1,BLUR_SIZE);
            break;
        case Gaussian:
            GaussianBlur(srcimage,dstimage,BLUR_SIZE,0,0);
            break;
        case MediaBlur:
            medianBlur(srcimage,dstimage,BLUR_LEN);
            break;
        case BilateralBlur:
            bilateralFilter(srcimage,dstimage,25,25*2,25/2);
            break;
        default:
            break;
    }
}

tStaticsMsg* ImageEffect::calcStatics(QImage *image,int x1, int y1, int x2, int y2)
{
    imageconvert(image);
    //opencv中横坐标对应的是点的x坐标，纵坐标对应的是点的y坐标，坐标系和qt不同.
    //Rect的坐标和qt里面一样，不过长宽需要自己算一下
    Rect rect(x1,y1,x2-x1,y2-y1);
    //利用两个Rect的交集，我们可以很轻松的避免图像裁剪区域越界的情况
    rect &= Rect(0, 0, nowimage.cols, nowimage.rows);
    if(rect.width <=0 || rect.height <=0){
        return nullptr;
    }
    Mat staticsroi = nowimage(rect);
    Mat staticsroi_yuv;
    Scalar tmp;
    tmp = mean(staticsroi);
    staticsMsg.average_rgb.R = tmp.val[0];
    staticsMsg.average_rgb.G = tmp.val[1];
    staticsMsg.average_rgb.B = tmp.val[2];
    staticsMsg.awb_gain.R = tmp.val[1]/tmp.val[0];
    staticsMsg.awb_gain.G = 1.0;
    staticsMsg.awb_gain.B = tmp.val[1]/tmp.val[2];
    staticsMsg.rgb_ratio.RG_ratio =  tmp.val[0]/tmp.val[1];
    staticsMsg.rgb_ratio.BG_ratio =  tmp.val[2]/tmp.val[1];
    cvtColor(staticsroi, staticsroi_yuv, COLOR_RGB2YUV);
    tmp = mean(staticsroi_yuv);
    staticsMsg.average_yuv.Y = tmp.val[0];
    staticsMsg.average_yuv.Cr = tmp.val[1];
    staticsMsg.average_yuv.Cb = tmp.val[2];
    staticsMsg.start_point.x = x1;
    staticsMsg.start_point.y = y1;
    staticsMsg.section_size.width = x2 - x1;
    staticsMsg.section_size.height = y2 - y1;
    qDebug() << x1 << y1 << x2 << y2;
    qDebug() << staticsMsg.average_rgb.R  << staticsMsg.average_rgb.G << staticsMsg.average_rgb.B;
    qDebug() << staticsMsg.awb_gain.R  << staticsMsg.awb_gain.G << staticsMsg.awb_gain.B;
    qDebug() << staticsMsg.average_yuv.Y  << staticsMsg.average_yuv.Cr << staticsMsg.average_yuv.Cb;
    return &staticsMsg;
}

void ImageEffect::calcImageHist(QImage *image,tHistViewData *histdata)
{
    imageconvert(image);
    //init
    for(int i=0;i<256;i++){
        histdata->r[i] = 0;
        histdata->g[i] = 0;
        histdata->b[i] = 0;
        histdata->y[i] = 0;
    }

    int channel = nowimage.channels();
    for(int i=0;i<nowimage.rows;i++){
        uchar* data = nowimage.ptr<uchar>(i);
        for(int j=0;j<nowimage.cols;j++){
            int tmp1 = data[channel*j];
            int tmp2 = data[channel*j+1];
            int tmp3 = data[channel*j+2];


            histdata->r[tmp1]++;
            histdata->g[tmp2]++;
            histdata->b[tmp3]++;
        }
    }
    Mat yuvImage;
    cvtColor(nowimage,yuvImage,COLOR_RGB2YUV);
    for(int i=0;i<yuvImage.rows;i++){
        uchar* data = yuvImage.ptr<uchar>(i);
        for(int j=0;j<yuvImage.cols;j++){
            histdata->y[data[channel*j]]++;
        }
    }
    return;
}
