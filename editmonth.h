#ifndef EDITMONTH_H
#define EDITMONTH_H

#include <QDialog>
#include "monthclass.h"

namespace Ui {
class EditMonth;
}

class EditMonth : public QDialog
{
    Q_OBJECT

public:
    explicit EditMonth(MonthClass& md, QWidget *parent = 0);
    void redraw();
    ~EditMonth();

private:
    Ui::EditMonth *ui;
    MonthClass monthData;

protected:
    virtual void resizeEvent(QResizeEvent *) { redraw(); }
};

#endif // EDITMONTH_H
