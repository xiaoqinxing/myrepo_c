#include "histgramview.h"
#include "ui_histgramview.h"

HistgramView::HistgramView(QWidget *parent) :
    QDialog(parent),
    x(256),
    r(256),
    ui(new Ui::HistgramView)
{
    ui->setupUi(this);
    for(int i=0;i<256;i++){
        x[i] = i;
        r[i] = i;
    }
    ui->widget->legend->setVisible(true);
    ui->widget->addGraph();
    ui->widget->graph(0)->setName("直方图");
}

HistgramView::~HistgramView()
{
    delete ui;
}

void HistgramView::on_r_enable_toggled(bool checked)
{
    if(checked == true){
        ui->widget->graph(0)->setBrush(QBrush(QColor(255,0,0)));
        ui->widget->graph(0)->setData(x,r);
    }
    else{
        ui->widget->removeGraph(0);
    }
}
