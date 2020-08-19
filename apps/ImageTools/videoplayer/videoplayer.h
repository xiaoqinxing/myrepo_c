#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

namespace Ui {
class videoplayer;
}

class videoplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit videoplayer(QWidget *parent = nullptr);
//    explicit videoplayer(QString &filename);
    void setSrcName(QString &filename);
    ~videoplayer();

private slots:
    void on_actionstart_triggered();

    void on_actionstop_triggered();

    void on_actionpause_triggered();

private:
    Ui::videoplayer *ui;
    VlcInstance *instance;
    VlcMedia *media;
    VlcMediaPlayer *player;
    QString url;
};

#endif // VIDEOPLAYER_H
