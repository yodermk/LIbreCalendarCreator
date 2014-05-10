#ifndef MONTHCLASS_H
#define MONTHCLASS_H
#include <QDate>
#include <QPaintDevice>

class MonthClass
{
private:
    QDate firstOfMonth;

public:
    MonthClass(QDate m);
    void drawPicturePage(QPaintDevice * pd);
    void drawCalendarPage(QPainter *painter, int w, int h);
    QString text();
    int dayOfWeek(int day);
    int weekOfMonth(int day);
};

#endif // MONTHCLASS_H
