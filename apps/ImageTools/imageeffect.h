#ifndef IMAGEEFFECT_H
#define IMAGEEFFECT_H

#include "opencv2/opencv.hpp"
using cv::Mat;
typedef enum{
    BoxBlur,
    Guassian
}typeBlur;
class ImageEffect
{
public:
    ImageEffect(Mat &inputImage, Mat &outputImage);
    void Blur(typeBlur type);
private:
    Mat image;
};

#endif // IMAGEEFFECT_H
