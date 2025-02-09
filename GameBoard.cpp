#include "GameBoard.h"
#include "Cell.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QPixmap>

// Constructor for GameBoard
GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent) {
    // Create a grid layout for the game board
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0); 
    gridLayout->setContentsMargins(0, 0, 0, 0); 
    setLayout(gridLayout);

    // Calculate the board size based on the number of rows and columns
    int boardWidth = numCols * 40;
    int boardHeight = numRows * 40;
    setFixedSize(boardWidth, boardHeight);  

    // Initialize the game (create cells, place mines, etc.)
    initializeGame();
}

// Initialize the game board
void GameBoard::initializeGame() {
    // Clear the cellStates vector and resize it to match the number of rows
    cellStates.clear();
    cellStates.resize(numRows);

    // Resize each inner vector to match the number of columns
    for (int i = 0; i < numRows; ++i) {
        cellStates[i].clear();
        cellStates[i].resize(numCols);
    }

    // Create and initialize Cell objects for each position on the board with fixed dsize
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            Cell *cell = new Cell(i, j, this);  
            cell->setFixedSize(40, 40); 
            cell->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); 

            // Connect cell signals to GameBoard slots
            connect(cell, &Cell::leftClicked, this, &GameBoard::onLeftClicked);
            connect(cell, &Cell::rightClicked, this, &GameBoard::onRightClicked);

            cellStates[i][j] = cell;
            gridLayout->addWidget(cell, i, j);
        }
    }

    // Initialize all cells to their default state (unrevealed, unflagged, no mine)
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cellStates[i][j]->setRevealed(false);
            cellStates[i][j]->setFlagged(false);
            cellStates[i][j]->setHasMine(false);
        }
    }

    // Place mines randomly on the board
    setMines();
}

// Handle left-click events on cells
void GameBoard::onLeftClicked(Cell* cell) {
    int i = cell->getRow();
    int j = cell->getCol();

    // If the clicked cell has a mine then handle the game over scenario
    if (cellStates[i][j]->hasMine()) {
        // Display the mine icon on the cell
        QPixmap pixmap("./bomb.png");
        QIcon mineIcon(pixmap);
        cell->setIcon(mineIcon);
        cell->setIconSize(QSize(40, 40));

        // Show a game over message box
        QMessageBox msgBox;
        msgBox.setWindowTitle("Game Over");
        msgBox.setText("You stepped on a mine!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.addButton(QMessageBox::Retry);
        msgBox.addButton(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Retry);

        // Wait for the user to click a button
        QMessageBox::StandardButton reply = (QMessageBox::StandardButton)msgBox.exec();

        // Restart or quit based on the user's choice
        if (reply == QMessageBox::Retry) {
            restart(); 
        } else {
            QApplication::quit();
        } 
    } 
    // If the cell is flagged, remove the flag and reveal adjacent cells
    else if (cellStates[i][j]->isFlagged()) {
        cell->setIcon(QIcon());
        cell->setFlagged(false);
        revealAdjacentCells(i, j);  
    } 
    // Otherwise, reveal adjacent cells
    else {
        revealAdjacentCells(i, j);  
    }

    // Check if the player has won (all non-mine cells revealed) and handle the game win scenario
    if (revealed == amountOfCells) {
        QPixmap pixmap("./win.jpg");
        pixmap = pixmap.scaled(40, 40, Qt::KeepAspectRatio);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Congratulations");
        msgBox.setText("You won!");
        msgBox.setIconPixmap(pixmap);
        
        msgBox.addButton(QMessageBox::Retry);
        msgBox.addButton(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Retry);

        // Wait for the user to click a button
        QMessageBox::StandardButton reply = (QMessageBox::StandardButton)msgBox.exec();

        // Restart or quit based on the user's choice
        if (reply == QMessageBox::Retry) {
            restart(); 
        } else {
            QApplication::quit();
        } 
    }
}

// Handle right-click events on cells (flagging/unflagging)
void GameBoard::onRightClicked(Cell* cell) {
    // If the cell is not flagged and not revealed, flag it
    if (!cell->isFlagged() && !cell->isRevealed()) {
        QPixmap pixmap("./flag.png");
        QIcon flagIcon(pixmap);
        cell->setIcon(flagIcon);
        cell->setIconSize(QSize(40, 40));
        cell->setFlagged(true);
    } 
    // If the cell is already flagged, unflag it
    else if (cell->isFlagged() && !cell->isRevealed()) {
        cell->setIcon(QIcon());
        cell->setFlagged(false);
    }
}

// Recursively reveal adjacent cells
void GameBoard::revealAdjacentCells(int row, int col) {
    // If the cell is out of bounds or already revealed, return
    if (row < 0 || row >= numRows || col < 0 || col >= numCols || cellStates[row][col]->isRevealed()) {
        return;
    }

    // Reveal the current cell
    cellStates[row][col]->setRevealed(true);
    cellStates[row][col]->setFlat(true);  // Remove the 3D button effect
    cellStates[row][col]->setStyleSheet("background-color: lightgray; border: none;");
    revealed++;  // Increment the revealed cell count

    // If the cell is flagged, remove the flag
    if (cellStates[row][col]->isFlagged()) {
        cellStates[row][col]->setIcon(QIcon());
        cellStates[row][col]->setFlagged(false);
    }

    // Calculate the number of adjacent mines
    int adjacentMineCount = calculateAdjacentMines(row, col);

    if (adjacentMineCount > 0) {
        // If the cell has adjacent mines, display the number and stop recursion
        cellStates[row][col]->setText(QString::number(adjacentMineCount));
        return;
    }

    // If no adjacent mines, recursively reveal neighbors
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) continue;  // Skip the current cell
            revealAdjacentCells(row + x, col + y);
        }
    }
}

// Calculate the number of adjacent mines for a given cell
int GameBoard::calculateAdjacentMines(int row, int col) {
    int adjacentMineCount = 0;

    // Loop through all neighboring cells (3x3 grid around the cell)
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int ni = row + x;
            int nj = col + y;

            if (ni >= 0 && ni < numRows && nj >= 0 && nj < numCols) {   
                if (cellStates[ni][nj]->hasMine()) {
                    adjacentMineCount++; 
                }
            }
        }
    }
    return adjacentMineCount;
}

// Place mines randomly on the board
void GameBoard::setMines() {
    QRandomGenerator *rand = QRandomGenerator::global();
    int minePlaced = 0;

    // Place mines until the total number of mines is reached
    while (minePlaced < totalMines) {
        int rowToPlace = rand->bounded(numRows);
        int colToPlace = rand->bounded(numCols);

        if (!(cellStates[rowToPlace][colToPlace]->hasMine())) {
            cellStates[rowToPlace][colToPlace]->setHasMine(true);
            minePlaced++;
        }
    }
}

// Destructor for GameBoard
GameBoard::~GameBoard() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (cellStates[i][j]) {
                delete cellStates[i][j];
                cellStates[i][j] = nullptr;
            }
        }
    }

    // Clear the cellStates vector
    cellStates.clear();
}

// Restart the game
void GameBoard::restart() {
    revealed = 0;  // Reset the revealed cell counter

    // Disconnect all signals from Cell objects
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (cellStates[i][j]) {
                cellStates[i][j]->disconnect();  // Disconnect all signals
            }
        }
    }

    // Remove and delete old cells
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (cellStates[i][j]) {
                gridLayout->removeWidget(cellStates[i][j]);  // Remove from layout
                cellStates[i][j]->deleteLater();  // Schedule for deletion
                cellStates[i][j] = nullptr;  // Set pointer to nullptr
            }
        }
    }

    // Clear the cellStates vector
    cellStates.clear();

    // Reinitialize the game
    initializeGame();
}