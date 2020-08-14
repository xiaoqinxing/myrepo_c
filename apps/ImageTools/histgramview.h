#ifndef HISTGRAMVIEW_H
#define HISTGRAMVIEW_H

#include <QDialog>

namespace Ui {
class HistgramView;
}

class HistgramView : public QDialog
{
    Q_OBJECT

public:
    explicit HistgramView(QWidget *parent = nullptr);
    ~HistgramView();
   QVector<double> x;
   QVector<double> r;
   QVector<double> g;
   QVector<double> b;
   QVector<double> y;

private slots:
    void on_r_enable_toggled(bool checked);

private:
    Ui::HistgramView *ui;
};

#endif // HISTGRAMVIEW_H
