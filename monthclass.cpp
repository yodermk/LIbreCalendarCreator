#include <QPainter>
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

    painter->drawText(xoffset+calwidth*4/10, yoffset, calwidth*6/10, calheight/20, Qt::AlignRight, text());

    if (!painter->isActive()) qDebug("isActive fail");
    // Draw horizontal lines
    for (counter=0; counter<7; counter++) {
        painter->drawLine(xoffset, yoffset+counter*weekheight, xoffset+calwidth, yoffset+counter*weekheight);
    }
    // Draw vertical lines
    for (counter=0; counter<8; counter++) {
        painter->drawLine(xoffset+counter*daywidth, yoffset, xoffset+counter*daywidth, yoffset+calheight);
    }
}

QString MonthClass::text()
{
    return firstOfMonth.toString("MMMM yyyy");
}
