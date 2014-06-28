#ifndef CHOOSECROPPHOTODIALOG_H
#define CHOOSECROPPHOTODIALOG_H

#include <QDialog>

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
};

#endif // CHOOSECROPPHOTODIALOG_H
