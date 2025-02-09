#include "Cell.h"
#include "QRightClickButton.h"
#include <QMouseEvent>

// Constructor for the Cell class
Cell::Cell(int row, int col, QWidget *parent)
    : QPushButton(parent), row(row), col(col), mine(false), revealed(false), adjacentMines(0), flagged(false) {
}

// Set whether the cell contains a mine
void Cell::setHasMine(bool mine) {
    this->mine = mine;
}

// Check if the cell contains a mine
bool Cell::hasMine() {
    return mine;
}

// Set the number of adjacent mines for this cell
void Cell::setAdjacentMines(int count) {
    adjacentMines = count;
}

// Get the number of adjacent mines for this cell
int Cell::getAdjacentMines() {
    return adjacentMines;
}

// Set whether the cell is revealed
void Cell::setRevealed(bool revealed) {
    this->revealed = revealed;
}

// Check if the cell is revealed
bool Cell::isRevealed() {
    return revealed;
}

// Set whether the cell is flagged
void Cell::setFlagged(bool flagged) {
    this->flagged = flagged;
}

// Check if the cell is flagged
bool Cell::isFlagged() {
    return flagged;
}

// Get the row index of the cell
int Cell::getRow() {
    return row;
}

// Get the column index of the cell
int Cell::getCol() {
    return col;
}

// Destructor for the Cell class
Cell::~Cell() {
    // Cleanup resources if necessary (currently empty)
}

// Handle mouse press events on the cell
void Cell::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit leftClicked(this);
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(this);
    }

    QPushButton::mousePressEvent(event);
}