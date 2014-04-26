#ifndef NEWCALENDAR_H
#define NEWCALENDAR_H

#include <QDialog>
#include <QDate>

namespace Ui {
class NewCalendar;
}

class NewCalendar : public QDialog
{
    Q_OBJECT

public:
    explicit NewCalendar(QWidget *parent = 0);
    ~NewCalendar();
    QDate startMonth, endMonth;

private:
    Ui::NewCalendar *ui;

private slots:
    void accept();
};

#endif // NEWCALENDAR_H
