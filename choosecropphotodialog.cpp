#include "choosecropphotodialog.h"
#include "ui_choosecropphotodialog.h"

ChooseCropPhotoDialog::ChooseCropPhotoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCropPhotoDialog)
{
    ui->setupUi(this);
    photoSelectionModel = new QFileSystemModel;
    ui->browserTreeView->setModel(photoSelectionModel);
    ui->browserTreeView->setRootIndex(photoSelectionModel->index(QDir::currentPath()));
}

ChooseCropPhotoDialog::~ChooseCropPhotoDialog()
{
    delete ui;
}
