#ifndef IMAGEEFFECT_H
#define IMAGEEFFECT_H

#include "opencv2/opencv.hpp"
#include "QFileInfo"
#include "QImage"
using cv::Mat;
typedef enum{
    BoxBlur,
    Gaussian
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
private:
    Mat srcimage;
    Mat dstimage;
    QImage *srcqimage;
    QImage *dstqimage;
};

#endif // IMAGEEFFECT_H
