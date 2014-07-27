#ifndef CHOOSECROPPHOTODIALOG_H
#define CHOOSECROPPHOTODIALOG_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class ChooseCropPhotoDialog;
}

class ChooseCropPhotoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCropPhotoDialog(QWidget *parent = 0);
    ~ChooseCropPhotoDialog();

private:
    Ui::ChooseCropPhotoDialog *ui;
    QFileSystemModel *photoSelectionModel;

private slots:
    void photoSelectionChanged(const QModelIndex &index);
    void accept();
};

#endif // CHOOSECROPPHOTODIALOG_H
