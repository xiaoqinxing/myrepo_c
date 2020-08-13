#ifndef STATICSVIEW_H
#define STATICSVIEW_H

#include <QDialog>

namespace Ui {
class StaticsView;
}
/*RGB*/
typedef struct{
    unsigned char R;
    unsigned char G;
    unsigned char B;
}tRgbColor;
typedef struct{
    float R;
    float G;
    float B;
}tfRgbColor;

/*YUV*/
typedef struct{
    unsigned char Y;
    unsigned char Cb;
    unsigned char Cr;
}tYuvColor;
typedef struct{
    float Y;
    float Cb;
    float Cr;
}tfYuvColor;

/*B/G R/G ratio*/
typedef struct{
    float RG_ratio;
    float BG_ratio;
}tfRatio;

typedef struct{
    int x;
    int y;
}tiPoint;

typedef struct{
    int width;
    int height;
}tiSize;

/*statics message*/
typedef struct{
    tfRgbColor average_rgb;
    tfYuvColor average_yuv;
    tfRgbColor snr_rgb;
    tfYuvColor snr_yuv;
    tfRatio rgb_ratio;
    tfRgbColor awb_gain;
    tiPoint start_point;
    tiSize section_size;
}tStaticsMsg;

class StaticsView : public QDialog
{
    Q_OBJECT

public:
    explicit StaticsView(QWidget *parent = nullptr);
    ~StaticsView();
    void Update(tStaticsMsg *msg);

private:
    Ui::StaticsView *ui;
};

#endif // STATICSVIEW_H
