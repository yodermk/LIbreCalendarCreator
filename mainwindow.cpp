#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newcalendar.h"
#include "editmonth.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>

const qint32 MagicNumber = 0x8D2789A8; // To identify the file type
const qint32 FileVersionNumber = 1;    // Increment each time Calendar file format changes

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    modified = false;
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(newCalendar()));
    connect(ui->monthList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editMonth(QListWidgetItem*)));
    connect(ui->action_Generate_Calendar, SIGNAL(triggered()), this, SLOT(generateCalendar()));
    connect(ui->action_Load, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));

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
    for (QDate iter = startMonth; iter <= endMonth; iter = iter.addMonths(1)) {
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
    writer.setPageOrientation(QPageLayout::Landscape);
    QPainter painter(&writer);
    painter.setPen(QPen(Qt::black, 0.1, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::black));

    writer.setCreator("Libre Calendar Creator");
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setTitle("Calendar " + months[0].text() + " - " + months[months.size()-1].text());
    for (currMonth = 0; currMonth < ui->monthList->count(); currMonth++) {
        if (!writer.newPage()) qDebug("newPage fail");
        months[currMonth].drawCalendarPage(&painter, writer.width(), writer.height());
        qDebug("hello " + months[currMonth].text().toLatin1());
    }
}

void MainWindow::load()
{
    QString selectedName = QFileDialog::getOpenFileName(this, "Load Calendar ...", ".",
                                                        "Calendar Files (*.librecal)");
    if (selectedName == QString()) {
        return;
    }

    qint32 magic;
    qint32 version;
    int startMonth, startYear, numMonths;
    QFile file(selectedName);
    if (!file.open(QIODevice::ReadOnly)) {
        ui->statusBar->showMessage("FAILED to open project!", 5000);
        return;
    }
    QDataStream in(&file);

    in >> magic >> version;

    if (magic != MagicNumber) {
        ui->statusBar->showMessage("This does not appear to be a LibreCalendar file.", 5000);
        return;
    }
    if (version > FileVersionNumber) {
        ui->statusBar->showMessage("This file was created by a newer version of Libre Calendar Creator", 5000);
        return;
    }

    months.clear();
    ui->monthList->clear();

    in >> startYear >> startMonth >> numMonths;
    QDate curMonth(startYear, startMonth, 1);

    for (int c=0; c<numMonths; c++) {
        MonthClass mc(curMonth, in, version);
        curMonth = curMonth.addMonths(1);
        ui->monthList->addItem(mc.text());
        months.append(mc);
    }
}

void MainWindow::save()
{
    if (fileName == QString()) {
        // If no name yet we need to get one
        QString selectedName = QFileDialog::getSaveFileName(this, "Save Calendar As ...", ".",
                                                            "Calendar Files (*.librecal)");
        if (selectedName == QString()) {
            ui->statusBar->showMessage("Cancelled save.", 5000);
            return;
        }
        if(!selectedName.endsWith(".librecal"))
            selectedName += ".librecal";
        fileName = selectedName;
        QFile file(selectedName);
        if (!file.open(QIODevice::WriteOnly)) {
            ui->statusBar->showMessage("FAILED to save project!", 5000);
            return;
        }
        QDataStream out(&file);

        // write header info, starting month, and number of months
        out << MagicNumber << FileVersionNumber;
        out << months[0].getYear() << months[0].getMonth();
        out << months.size();

        for (int currMonth = 0; currMonth < ui->monthList->count(); currMonth++) {
            months[currMonth].save(out);
        }

        ui->statusBar->showMessage("Successfully saved calendar!", 5000);
    }
}
