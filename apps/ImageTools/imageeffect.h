#ifndef IMAGEEFFECT_H
#define IMAGEEFFECT_H

#include "opencv2/opencv.hpp"
#include "QFileInfo"
#include "QImage"
using cv::Mat;
typedef enum{
    BoxBlur,
    Gaussian,
    MediaBlur,
    BilateralBlur
}typeBlur;
typedef struct{
    unsigned char R;
    unsigned char G;
    unsigned char B;
}tPointColor;
class ImageEffect
{
public:
    ImageEffect(QFileInfo file);
    ~ImageEffect();
    void Blur(typeBlur type);
    void saveimage(QImage* image,QString filename);
    QImage* getSrcImage();
    QImage* getDstImage();
    tPointColor getImagePoint(QImage* image, int x, int y);
private:
    Mat srcimage;
    Mat dstimage;
    Mat nowimage;
    QImage *srcqimage;
    QImage *dstqimage;
    void imageconvert(QImage* image);
};

#endif // IMAGEEFFECT_H
