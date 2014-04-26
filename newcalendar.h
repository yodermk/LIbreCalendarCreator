#ifndef NEWCALENDAR_H
#define NEWCALENDAR_H

#include <QDialog>

namespace Ui {
class NewCalendar;
}

class NewCalendar : public QDialog
{
    Q_OBJECT

public:
    explicit NewCalendar(QWidget *parent = 0);
    ~NewCalendar();

private:
    Ui::NewCalendar *ui;
};

#endif // NEWCALENDAR_H
