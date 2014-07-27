#include "photocropper.h"

PhotoCropper::PhotoCropper(QWidget *parent) :
    QWidget(parent)
{
}

void PhotoCropper::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRect myRect(0,0,this->width(), this->height());
    painter.drawImage(myRect, img); // first just draw the original image
    if (mode>0) {
        // unless mode 0 (no selection), probably want to:
        // 1. Dim the entire image
        painter.fillRect(myRect, dimColor);
        // 2. Draw selected area normal color
        painter.drawImage(currentCrop, img, cropInOrig());
        // 3. Draw handle type things around the edges0
        // (for now, a little white square at each corner)
        QPoint corners[] = {QPoint(currentCrop.left(), currentCrop.top()),
                            QPoint(currentCrop.right(), currentCrop.top()),
                            QPoint(currentCrop.left(), currentCrop.bottom()),
                            QPoint(currentCrop.right(), currentCrop.bottom())};
        QPoint adj(5, 5); // corner handles start 5 pixels up and left of corner point
        QPoint cornerSize(10, 10); // 10x10 pixels total
        for(int i=0; i<4; i++)
            painter.fillRect(QRect(corners[i]-adj, cornerSize), Qt::white);
    }
}

QImage PhotoCropper::cropped()
{
    // return cropInOrig();
}

void PhotoCropper::newPhoto(QString filename)
{
    img = QImage(filename);
    imageFileName = filename;
    currentCrop = QRect();
    update();
    scalex = img.width() / this->width();
    scaley = img.height() / this->height();
}

QRect PhotoCropper::cropInOrig()
{
    return QRect(currentCrop.left()*scalex,
                 currentCrop.top()*scaley,
                 currentCrop.width()*scalex,
                 currentCrop.height()*scaley);
}

void PhotoCropper::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        startDrag = e->pos();
        mode = 1;
        repaint();
    }
}

void PhotoCropper::mouseMoveEvent(QMouseEvent *e)
{
    if (mode == 1) { // no need to redraw if dragging not in progress
        mousePos = e->pos();
        repaint();
        currentCrop = QRect(startDrag, mousePos);
    }
}

void PhotoCropper::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePos = e->pos();
        if (mousePos == startDrag) {
            mode = 0; // revert!
            return;
        }
        mode = 2;
        currentCrop = QRect(startDrag, mousePos);
        repaint();
    }
}

