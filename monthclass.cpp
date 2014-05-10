#include <QPainter>
#include <QRect>
#include <QMargins>
#include "monthclass.h"


MonthClass::MonthClass(QDate m) : firstOfMonth(m.year(), m.month(), 1)
{

}

void MonthClass::drawPicturePage(QPaintDevice *pd)
{
    QPainter painter(pd);
    int h = pd->height();
    int w = pd->width();
}

void MonthClass::drawCalendarPage(QPainter *painter, int w, int h)
{
    int calheight = h*8/10;  // leave some room
    int adj = calheight % 6;
    calheight -= adj; // This should eliminate the lines "jutting" past the end
    int weekheight = calheight/6;  // pixel height of each week
    int calwidth = w*8/10;   // leave some room
    adj = calwidth % 7;
    calwidth -= adj;
    int daywidth = calwidth/7;     // pixel width of each day
    int xoffset = w/10;  // go this far to the right before starting
    int yoffset = h/10;  // go this far down before starting
    int counter;

    painter->setPen(Qt::black); // well, actually what the pen should be for the month name and grid
    painter->drawText(xoffset+calwidth*4/10, yoffset/2, calwidth*6/10, calheight/20, Qt::AlignRight, text());

    auto dayRect = [=] (int day) -> QRect {
        return QRect(xoffset+daywidth*dayOfWeek(day),
                     yoffset+weekheight*(weekOfMonth(day)-1),
                     daywidth, weekheight); };

    if (!painter->isActive()) qDebug("isActive fail");
    // Draw horizontal lines
    for (counter=0; counter<7; counter++) {
        painter->drawLine(xoffset, yoffset+counter*weekheight, xoffset+calwidth, yoffset+counter*weekheight);
    }
    // Draw vertical lines
    for (counter=0; counter<8; counter++) {
        painter->drawLine(xoffset+counter*daywidth, yoffset, xoffset+counter*daywidth, yoffset+calheight);
    }

    QPen sundayNum(Qt::red);
    QPen normalNum(Qt::black);
    QMargins textInBox(15,5,15,5);
    painter->setFont(QFont("Helvetica", 10));
    // put in day numbers
    for (int d=1; d<=firstOfMonth.daysInMonth(); d++) {
        if (dayOfWeek(d)==0)
            painter->setPen(sundayNum);
        else
            painter->setPen(normalNum);
        QRect r=dayRect(d); // actual box we'll use to draw the day #
        r -= textInBox;     // give it some padding
        painter->drawText(r, Qt::AlignRight, QString("%1").arg(d));
    }
}

QString MonthClass::text()
{
    return firstOfMonth.toString("MMMM yyyy");
}

int MonthClass::dayOfWeek(int day)
{
    int d = firstOfMonth.dayOfWeek();
    if (d == 7) // Sunday
        d = 0;  // we want 0 based
    d += day-1;
    return d % 7;
}

int MonthClass::weekOfMonth(int day)
{
    int f = dayOfWeek(1);   // day of week of first day of month
    int start2ndWk = 8-f;   // date of start of second week
    int w=1;
    for (int c=start2ndWk; c<=day; c+=7,w++) {}
    return w;
}
