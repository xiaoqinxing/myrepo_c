#include "rtspconfigview.h"
#include "ui_rtspconfigview.h"
#include "QSettings"

RtspConfigView::RtspConfigView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RtspConfigView)
{
    ui->setupUi(this);
}

RtspConfigView::~RtspConfigView()
{
    delete ui;
}

void RtspConfigView::show()
{
    QSettings settings("config", "ImageTool", this);
    ui->username->setText(settings.value("rtsp_username","admin").toString());
    ui->password->setText(settings.value("rtsp_password","admin123").toString());
    ui->ip->setText(settings.value("rtsp_ip","127.0.0.1").toString());
    ui->port->setText(settings.value("rtsp_port","1554").toString());
    QDialog::show();
}

void RtspConfigView::on_buttonBox_accepted()
{
    QSettings settings("config", "ImageTool", this);
    settings.setValue("rtsp_username",ui->username->text());
    settings.setValue("rtsp_password",ui->password->text());
    settings.setValue("rtsp_ip",ui->ip->text());
    settings.setValue("rtsp_port",ui->port->text());
    rtsp_address = "rtsp://"+ui->username->text()+":"+ui->password->text()
            +"@" + ui->ip->text() + ":" + ui->port->text();
}

QString* RtspConfigView::getRtspAddress()
{
    return &rtsp_address;
}
