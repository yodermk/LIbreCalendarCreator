#ifndef EDITMONTH_H
#define EDITMONTH_H

#include <QDialog>

namespace Ui {
class EditMonth;
}

class EditMonth : public QDialog
{
    Q_OBJECT

public:
    explicit EditMonth(QWidget *parent = 0);
    ~EditMonth();

private:
    Ui::EditMonth *ui;
};

#endif // EDITMONTH_H
