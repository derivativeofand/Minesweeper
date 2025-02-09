#ifndef QRIGHTCLICKBUTTON_h
#define QRIGHTCLICKBUTTON_h

#include <QPushButton>
#include <QMouseEvent>

// QRightClickButton class definition
class QRightClickButton : public QPushButton {
    Q_OBJECT

public: 
    // Constructor for the QRightClickButton class
    explicit QRightClickButton(QWidget* parent = nullptr);

protected:
    // Reimplement the mousePressEvent to handle right-click events specifically
    void mousePressEvent(QMouseEvent* e);

signals:
    // Signal emitted when the right mouse button is clicked on the button
    void rightClicked();
};

#endif
