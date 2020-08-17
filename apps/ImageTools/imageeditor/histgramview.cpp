#include "histgramview.h"
#include "ui_histgramview.h"

HistgramView::HistgramView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistgramView)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowMaximizeButtonHint);
    ui->widget->legend->setVisible(true);
    r_graph = ui->widget->addGraph();
    r_graph->setPen(QPen(Qt::red));
    r_graph->setName("R");
    g_graph = ui->widget->addGraph();
    g_graph->setPen(QPen(Qt::green));
    g_graph->setName("G");
    b_graph = ui->widget->addGraph();
    b_graph->setPen(QPen(Qt::blue));
    b_graph->setName("B");
    y_graph = ui->widget->addGraph();
    y_graph->setPen(QPen(Qt::black));
    y_graph->setName("Y");

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->widget->xAxis2->setVisible(true);
    ui->widget->xAxis2->setTickLabels(false);
    ui->widget->yAxis2->setVisible(true);
    ui->widget->yAxis2->setTickLabels(false);

    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    // 初始化数据
    histviewData.x.resize(256);
    histviewData.r.resize(256);
    histviewData.g.resize(256);
    histviewData.b.resize(256);
    histviewData.y.resize(256);

    for(int i=0;i<256;i++){
        histviewData.x[i] = i;
    }

    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

HistgramView::~HistgramView()
{
    ui->widget->removeGraph(r_graph);
    ui->widget->removeGraph(g_graph);
    ui->widget->removeGraph(b_graph);
    ui->widget->removeGraph(y_graph);
    delete ui;
}

tHistViewData* HistgramView::getHistviewDataPtr()
{
    return &histviewData;
}

void HistgramView::show()
{
    //填充数据
    r_graph->setData(histviewData.x,histviewData.r);
    g_graph->setData(histviewData.x,histviewData.g);
    b_graph->setData(histviewData.x,histviewData.b);
    y_graph->setData(histviewData.x,histviewData.y);
    ui->widget->xAxis->rescale(true);
    ui->widget->yAxis->rescale(true);
    // 立即刷新图像
    ui->widget->replot();
    QDialog::show();
}

void HistgramView::on_r_enable_toggled(bool checked)
{
     r_graph->setVisible(checked);
     ui->widget->replot();
}

void HistgramView::on_g_enable_toggled(bool checked)
{
    g_graph->setVisible(checked);
    ui->widget->replot();
}

void HistgramView::on_b_enable_toggled(bool checked)
{
    b_graph->setVisible(checked);
    ui->widget->replot();
}

void HistgramView::on_y_enable_toggled(bool checked)
{
    y_graph->setVisible(checked);
    ui->widget->replot();
}
