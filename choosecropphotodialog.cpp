#include "choosecropphotodialog.h"
#include "ui_choosecropphotodialog.h"

ChooseCropPhotoDialog::ChooseCropPhotoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCropPhotoDialog)
{
    ui->setupUi(this);
}

ChooseCropPhotoDialog::~ChooseCropPhotoDialog()
{
    delete ui;
}
