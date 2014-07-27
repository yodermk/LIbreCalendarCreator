#include "choosecropphotodialog.h"
#include "ui_choosecropphotodialog.h"
#include <QMessageBox>
#include <QSettings>

ChooseCropPhotoDialog::ChooseCropPhotoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCropPhotoDialog)
{
    ui->setupUi(this);
    photoSelectionModel = new QFileSystemModel;
    ui->browserTreeView->setModel(photoSelectionModel);
    ui->browserTreeView->setCurrentIndex(photoSelectionModel->index(QDir::currentPath()));
    photoSelectionModel->setRootPath("/home/micah");
    connect(ui->browserTreeView, SIGNAL(activated(QModelIndex)), this, SLOT(photoSelectionChanged(QModelIndex)));
    ui->browserTreeView->setColumnWidth(0, 400);
}

ChooseCropPhotoDialog::~ChooseCropPhotoDialog()
{
    delete ui;
}

void ChooseCropPhotoDialog::photoSelectionChanged(const QModelIndex &index)
{
    // a new photo in the tree view has just been selected by the user. Load it into the viewer/cropper!

    auto idx = ui->browserTreeView->selectionModel()->selectedIndexes()[0];
    QString path = photoSelectionModel->filePath(idx);
    // determine if it is an image
    if (  path.endsWith(".jpg", Qt::CaseInsensitive) ||
          path.endsWith(".jpeg", Qt::CaseInsensitive) ||
          path.endsWith(".png", Qt::CaseInsensitive) ||
          path.endsWith(".tif", Qt::CaseInsensitive) ||
          path.endsWith(".tiff", Qt::CaseInsensitive) ||
          path.endsWith(".gif", Qt::CaseInsensitive) ) {
        ui->cropWidget->newPhoto(path);
    }

}

void ChooseCropPhotoDialog::accept()
{
    QSettings settings;
    settings.setValue("savedir", "");
}
