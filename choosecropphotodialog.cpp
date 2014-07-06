#include "choosecropphotodialog.h"
#include "ui_choosecropphotodialog.h"

ChooseCropPhotoDialog::ChooseCropPhotoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCropPhotoDialog)
{
    ui->setupUi(this);
    photoSelectionModel = new QFileSystemModel;
    ui->browserTreeView->setModel(photoSelectionModel);
    ui->browserTreeView->setCurrentIndex(photoSelectionModel->index(QDir::currentPath()));
    connect(ui->browserTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(photoSelectionChanged(QModelIndex)));
}

ChooseCropPhotoDialog::~ChooseCropPhotoDialog()
{
    delete ui;
}

void ChooseCropPhotoDialog::photoSelectionChanged(const QModelIndex &index)
{
    // a new photo in the tree view has just been selected by the user. Load it into the viewer/cropper!
    qDebug(photoSelectionModel->data(index).toString().toLatin1());
}
