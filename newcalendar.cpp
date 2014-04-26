#include "newcalendar.h"
#include "ui_newcalendar.h"

NewCalendar::NewCalendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCalendar)
{
    ui->setupUi(this);
    QDate start = QDate::currentDate();
    start = start.addMonths(1);   // next month!
    QDate end = start.addMonths(12);
    ui->monthFromWidget->setDate(start);
    ui->monthToWidget->setDate(end);
}

NewCalendar::~NewCalendar()
{
    delete ui;
}

void NewCalendar::accept()
{
    startMonth = ui->monthFromWidget->date();
    startMonth = QDate(startMonth.year(), startMonth.month(), 5);
    endMonth = ui->monthToWidget->date();
    endMonth = QDate(endMonth.year(), endMonth.month(), 1); // not the 1st, for the sake of looping in the main class

    QDialog::accept();
}
