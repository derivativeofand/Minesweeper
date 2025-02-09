#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include <QVector>

// Cell class inheriting from QPushButton.
class Cell : public QPushButton {
    Q_OBJECT

public:
    // Constructor for the Cell class
    explicit Cell(int row, int col, QWidget* parent = nullptr);

    // Destructor for the Cell class
    ~Cell();
    
    // Mine setter and getter
    void setHasMine(bool mine);
    bool hasMine();

    // Adjacent mines setter and getter
    void setAdjacentMines(int count);
    int getAdjacentMines(); 

    // Reveal status setter and getter
    void setRevealed(bool revealed);
    bool isRevealed();

    // Flagged status setter and getter
    void setFlagged(bool flagged);
    bool isFlagged();

    // Row and column index setters and getters
    int getRow();
    int getCol();

protected:
    // Handle mouse press events on the cell
    void mousePressEvent(QMouseEvent *event) override;

signals:
    // Signal emitted when the cell is left-clicked
    void leftClicked(Cell* cell);
    
    // Signal emitted when the cell is right-clicked
    void rightClicked(Cell* cell);

private:
    // Member variables to store the row, column, and state of the cell
    int row;            
    int col;            
    bool mine;          
    bool revealed;      
    int adjacentMines;  
    bool flagged; 
};

#endif
