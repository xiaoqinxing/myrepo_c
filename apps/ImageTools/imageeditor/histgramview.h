#ifndef HISTGRAMVIEW_H
#define HISTGRAMVIEW_H

#include <QDialog>
#include "qcustomplot.h"
#include "imagecommon.h"
namespace Ui {
class HistgramView;
}

class HistgramView : public QDialog
{
    Q_OBJECT

public:
    explicit HistgramView(QWidget *parent = nullptr);
    ~HistgramView();
    tHistViewData* getHistviewDataPtr();
    void show();
   QCPGraph *r_graph,*g_graph,*b_graph,*y_graph;

private slots:
    void on_r_enable_toggled(bool checked);

    void on_g_enable_toggled(bool checked);

    void on_b_enable_toggled(bool checked);

    void on_y_enable_toggled(bool checked);

private:
    Ui::HistgramView *ui;
    tHistViewData histviewData;
};

#endif // HISTGRAMVIEW_H
