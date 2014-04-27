#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newcalendar.h"
#include "editmonth.h"
#include <QPdfWriter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modified = false;
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(newCalendar()));
    connect(ui->monthList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editMonth(QListWidgetItem*)));
    connect(ui->action_Generate_Calendar, SIGNAL(triggered()), this, SLOT(generateCalendar()));

    startMonth = QDate();
    endMonth = QDate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newCalendar()
{
    NewCalendar nc(this);
    int result = nc.exec();
    if (result == QDialog::Rejected)
        return;

    // set up the months in the main widget and the internal MonthClass list
    ui->monthList->clear();
    months.clear();
    startMonth = nc.startMonth;
    endMonth = nc.endMonth;
    for (QDate iter = startMonth; iter < endMonth; iter = iter.addMonths(1)) {
        MonthClass mc(iter);
        ui->monthList->addItem(mc.text());
        months.append(mc);
    }
}

void MainWindow::editMonth(QListWidgetItem * item)
{
    int index = ui->monthList->row(item);
    qDebug(months[index].text().toLatin1());
    EditMonth ed(months[index]);
    int result = ed.exec();
}

void MainWindow::generateCalendar()
{
    int currMonth;
    QPdfWriter writer("/home/micah/Calendar.pdf");
    writer.setCreator("Libre Calendar Creator");
    writer.setPageSize(QPagedPaintDevice::A4);
    for (currMonth = 0; currMonth < ui->monthList->count(); currMonth++) {
        writer.newPage();
        months[currMonth].drawCalendarPage(&writer);
        qDebug("hello " + months[currMonth].text().toLatin1());
    }
}
