#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>       
#include <QGridLayout>
#include <QVector>
#include "Cell.h" 

// GameBoard class definition
class GameBoard : public QWidget {
    Q_OBJECT  // Enable Qt's meta-object features (signals, slots, etc.)

public:
    // Constructor
    explicit GameBoard(QWidget *parent = nullptr);

    // Destructor
    ~GameBoard();

    // Public function to restart the game
    void restart();

public slots:
    // Slot to handle left-click events on cells
    void onLeftClicked(Cell* cell);

    // Slot to handle right-click events on cells (flagging/unflagging)
    void onRightClicked(Cell* cell);

private:
    // Initialize the game board (create cells, place mines, etc.)
    void initializeGame();

    // Randomly place mines on the board
    void setMines();

    // Calculate the number of adjacent mines for a given cell
    int calculateAdjacentMines(int row, int col);

    // Recursively reveal adjacent cells if there are no mines nearby
    void revealAdjacentCells(int row, int col);

    // Disable cells (e.g., after game over)
    void disableCells(int row, int col);

    // Layout manager for arranging cells in a grid
    QGridLayout *gridLayout;

    // Constants for the game board dimensions
    const int numRows = 16;  // Number of rows in the game board
    const int numCols = 30;  // Number of columns in the game board

    // Game configuration
    int totalMines = 99;  // Total number of mines on the board
    int amountOfCells = (numRows * numCols) - totalMines;  // Number of safe cells
    int revealed;  // Counter for the number of revealed cells

    // 2D vector to store pointers to Cell objects
    QVector<QVector<Cell*>> cellStates;
};

#endif // GAMEBOARD_H