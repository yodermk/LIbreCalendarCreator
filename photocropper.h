#ifndef PHOTOCROPPER_H
#define PHOTOCROPPER_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QMouseEvent>

class PhotoCropper : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoCropper(QWidget *parent = 0);
    QImage cropped();

signals:

public slots:
    void newPhoto(QString filename);

private:
    QString imageFileName;
    QImage img;
    QRect currentCrop;
    QPoint startDrag, mousePos;
    int scalex, scaley;
    QColor dimColor = QColor(0,0,0,40); // black with 40/255 alpha
    QRect cropInOrig();

    int mode = 0;
    // ^^ selection mode
    // 0 = nothing selected or in progress
    // 1 = user dragging to select
    // 2 = selection made

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
};

#endif // PHOTOCROPPER_H
