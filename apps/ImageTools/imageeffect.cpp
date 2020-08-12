#include "imageeffect.h"
using namespace cv;
ImageEffect::ImageEffect(Mat &inputImage, Mat &outputImage)
{
    outputImage = inputImage.clone();
    image = outputImage;
}

void ImageEffect::Blur(typeBlur type)
{
    if(type == BoxBlur)
        boxFilter(image,image,-1,Size(3,3));
}
