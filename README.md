# Minesweeper

## Introduction
This is a Minesweeper game developed as part of the CS 3307 assignment. The game is implemented using **C++** and the **Qt framework** for its graphical user interface (GUI). The project is designed to work in a Unix/Linux environment with support for graphical display via **X11**.

### Software Dependencies:
1. **C++ Compiler**
   - GCC or Clang

2. **Qt Framework**
   - Qt 5 or higher (Ensure that the Qt development tools, such as `qmake`, are installed)

3. **Ubuntu / WSL (Windows Subsystem for Linux)**
   - This project was developed using **Ubuntu** on **WSL**. It is recommended to use Ubuntu or another Linux distribution for running the game.


## Running the game
1. **Install Dependencies**:
   - Make sure that the necessary tools are installed. You can install the required dependencies using:
     sudo apt update
     sudo apt install build-essential qt5-qmake qtbase5-dev qtchooser
     ```
2. **Build the Project**:
   - Navigate to the project directory and run the build command to compile the code:
     qmake minesweeper.pro
     make
     ```

3. **Run the Game**
    - ./minesweeper

-If you are using **Windows with WSL**, ensure that **VcXsrv** or **Xming** is running before launching the game.

#### Icons References
Mine Icon - https://is1-ssl.mzstatic.com/image/thumb/Purple116/v4/76/0f/88/760f8811-6ecd-055b-3148-7c83e367f392/AppIcon-0-0-1x_U007emarketing-0-7-0-85-220.png/512x512bb.jpg

Question Mark Icon - https://upload.wikimedia.org/wikipedia/commons/thumb/d/d9/Icon-round-Question_mark.svg/1200px-Icon-round-Question_mark.svg.png

Winner Icon - https://upload.wikimedia.org/wikipedia/commons/8/87/Smiley_Face.JPG


