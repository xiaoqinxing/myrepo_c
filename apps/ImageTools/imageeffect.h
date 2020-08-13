#ifndef IMAGEEFFECT_H
#define IMAGEEFFECT_H

#include "opencv2/opencv.hpp"
#include "QFileInfo"
#include "QImage"
#include "QRect"
#include "imagecommon.h"
using cv::Mat;
/*滤波类型*/
typedef enum{
    BoxBlur,
    Gaussian,
    MediaBlur,
    BilateralBlur
}typeBlur;

class ImageEffect
{
public:
    ImageEffect(QFileInfo file);
    ~ImageEffect();
    void Blur(typeBlur type);
    void saveimage(QImage* image,QString filename);
    QImage* getSrcImage();
    QImage* getDstImage();
    tRgbColor getImagePoint(QImage* image, int x, int y);
    tStaticsMsg* calcStatics(QImage* image,int x1, int y1, int x2, int y2);
private:
    Mat srcimage;
    Mat dstimage;
    Mat nowimage;
    QImage *srcqimage;
    QImage *dstqimage;
    tStaticsMsg staticsMsg;
    void imageconvert(QImage* image);
};

#endif // IMAGEEFFECT_H
