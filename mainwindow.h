#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDate>
#include <QList>
#include "monthclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool modified;
    QDate startMonth, endMonth;
    QList<MonthClass> months;

public slots:
    void newCalendar();
    void editMonth(QListWidgetItem* item);
    void generateCalendar();
};

#endif // MAINWINDOW_H
