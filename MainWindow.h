#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameBoard.h"

// MainWindow class definition
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor for the MainWindow class
    MainWindow(QWidget *parent = nullptr);

private:
    // Pointer to the GameBoard object
    GameBoard *gameBoard;
};

#endif
