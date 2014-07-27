#ifndef MONTHCLASS_H
#define MONTHCLASS_H
#include <QDate>
#include <QPaintDevice>
#include <QDataStream>
#include <QImage>
#include <QRect>

class MonthClass
{
private:
    QDate firstOfMonth;
    QImage photoImg;
    QString photoPath;
    QRect photoCrop;

public:
    MonthClass(QDate m);
    MonthClass(QDate m, QDataStream &in, int fileVersion);
    void drawPicturePage(QPaintDevice * pd);
    void drawCalendarPage(QPainter *painter, int w, int h);
    QString text();
    int dayOfWeek(int day);
    int weekOfMonth(int day);
    int save(QDataStream &out);
    int getMonth() { return firstOfMonth.month(); }
    int getYear() { return firstOfMonth.year(); }
};

#endif // MONTHCLASS_H
