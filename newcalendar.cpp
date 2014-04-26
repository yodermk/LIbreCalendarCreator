#include "newcalendar.h"
#include "ui_newcalendar.h"

NewCalendar::NewCalendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCalendar)
{
    ui->setupUi(this);
}

NewCalendar::~NewCalendar()
{
    delete ui;
}
