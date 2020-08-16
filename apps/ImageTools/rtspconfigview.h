#ifndef RTSPCONFIGVIEW_H
#define RTSPCONFIGVIEW_H

#include <QDialog>

namespace Ui {
class RtspConfigView;
}

class RtspConfigView : public QDialog
{
    Q_OBJECT

public:
    explicit RtspConfigView(QWidget *parent = nullptr);
    ~RtspConfigView();
    void show();
    QString* getRtspAddress();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RtspConfigView *ui;
    QString rtsp_address;
};

#endif // RTSPCONFIGVIEW_H
