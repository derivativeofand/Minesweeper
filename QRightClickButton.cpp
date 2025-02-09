#include "QRightClickButton.h"

// Constructor for the QRightClickButton class
QRightClickButton::QRightClickButton(QWidget* parent) :
    QPushButton(parent) {}

// Handle mouse press events on the button
void QRightClickButton::mousePressEvent(QMouseEvent* e) {
    if(e->button() == Qt::RightButton) {
        emit rightClicked();
    } else {
        QPushButton::mousePressEvent(e);
    }
}
