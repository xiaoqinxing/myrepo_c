#ifndef STATICSVIEW_H
#define STATICSVIEW_H

#include <QDialog>
#include "imagecommon.h"

namespace Ui {
class StaticsView;
}

class StaticsView : public QDialog
{
    Q_OBJECT

public:
    explicit StaticsView(QWidget *parent = nullptr);
    ~StaticsView();
    void Update(tStaticsMsg *msg);

private:
    Ui::StaticsView *ui;
};

#endif // STATICSVIEW_H
