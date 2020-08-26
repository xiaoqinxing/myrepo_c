#include "videoplayer.h"
#include "ui_videoplayer.h"

videoplayer::videoplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::videoplayer),
    url()
{
    ui->setupUi(this);
//    VlcCommon::setPluginPath("./plugins");
    instance = new VlcInstance(VlcCommon::args(), this);

    player = new VlcMediaPlayer(instance);
    player->setVideoWidget(ui->widget);
}

videoplayer::~videoplayer()
{
    delete ui;
    delete media;
    delete player;
    delete instance;
}
void videoplayer::setSrcName(QString &filename)
{
    url = filename;
//    if(!url.isEmpty()){
//        media = new VlcMedia(url, instance);
//        player->open(media);
//    }
}


void videoplayer::on_actionstart_triggered()
{
    if(!url.isEmpty()){
        media = new VlcMedia(url, instance);
        player->open(media);
    }
}

void videoplayer::on_actionstop_triggered()
{
    player->stop();
}

void videoplayer::on_actionpause_triggered()
{
    player->togglePause();
}
