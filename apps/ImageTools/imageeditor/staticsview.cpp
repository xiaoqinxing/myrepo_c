#include "staticsview.h"
#include "ui_staticsview.h"

StaticsView::StaticsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StaticsView)
{
    ui->setupUi(this);
}

StaticsView::~StaticsView()
{
    delete ui;
}

void StaticsView::Update(tStaticsMsg *msg)
{
    ui->average_r->setValue(msg->average_rgb.R);
    ui->average_g->setValue(msg->average_rgb.G);
    ui->average_b->setValue(msg->average_rgb.B);
    ui->average_y->setValue(msg->average_yuv.Y);
    ui->average_cr->setValue(msg->average_yuv.Cr);
    ui->average_cb->setValue(msg->average_yuv.Cb);

    ui->snr_r->setValue(msg->snr_rgb.R);
    ui->snr_g->setValue(msg->snr_rgb.G);
    ui->snr_b->setValue(msg->snr_rgb.B);
    ui->snr_y->setValue(msg->snr_yuv.Y);
    ui->snr_cr->setValue(msg->snr_yuv.Cr);
    ui->snr_cb->setValue(msg->snr_yuv.Cb);

    ui->section_x->setValue(msg->start_point.x);
    ui->section_y->setValue(msg->start_point.y);
    ui->section_width->setValue(msg->section_size.width);
    ui->section_height->setValue(msg->section_size.height);

    ui->rg_ratio->setValue(msg->rgb_ratio.RG_ratio);
    ui->bg_ratio->setValue(msg->rgb_ratio.BG_ratio);

    ui->r_gain->setValue(msg->awb_gain.R);
    ui->g_gain->setValue(msg->awb_gain.G);
    ui->b_gain->setValue(msg->awb_gain.B);
}
