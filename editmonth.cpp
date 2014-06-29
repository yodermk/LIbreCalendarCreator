#include <QPixmap>
#include <QPainter>
#include "editmonth.h"
#include "ui_editmonth.h"
#include "choosecropphotodialog.h"

EditMonth::EditMonth(MonthClass& md, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMonth),
    monthData(md)
{
    ui->setupUi(this);
    connect(ui->btnChangePhoto, SIGNAL(clicked()), this, SLOT(chooseAndCropPhoto()));
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

void EditMonth::chooseAndCropPhoto()
{
    ChooseCropPhotoDialog diag(this);
    int result = diag.exec();
    if (result == QDialog::Rejected)
        return;

    // Now set the
}
