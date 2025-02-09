#include "MainWindow.h"
#include "GameBoard.h"

// Constructor for the MainWindow class
MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent) {

    // Set the title of the window
    setWindowTitle("MineSweeper");

    // Set a fixed size for the main window (1200px by 640px)
    setFixedSize(1200, 640);

    // Create an instance of the GameBoard class and set it as the central widget of the main window
    gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);
}
