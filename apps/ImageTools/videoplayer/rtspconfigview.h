#ifndef RTSPCONFIGVIEW_H
#define RTSPCONFIGVIEW_H

#include <QDialog>
#include <videoplayer.h>
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

signals:
    void rtspconfig_signal(QString url);
};

#endif // RTSPCONFIGVIEW_H
