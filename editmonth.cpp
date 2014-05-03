#include <QPixmap>
#include <QPainter>
#include "editmonth.h"
#include "ui_editmonth.h"

EditMonth::EditMonth(MonthClass& md, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMonth),
    monthData(md)
{
    ui->setupUi(this);
    redraw();
}

void EditMonth::redraw()
{
    QPixmap photoPage(ui->imgPhotoPage->width(), ui->imgPhotoPage->height());
    QPixmap calPage(ui->imgCalendarPage->width(), ui->imgCalendarPage->height());
    calPage.fill(); // default is white
    QPainter p(&calPage);
    monthData.drawCalendarPage(&p, calPage.width(), calPage.height());
    monthData.drawPicturePage(&photoPage);
    ui->imgCalendarPage->setPixmap(calPage);
    ui->imgPhotoPage->setPixmap(photoPage);
}

EditMonth::~EditMonth()
{
    delete ui;
}
