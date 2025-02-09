#include "MainWindow.h"
#include <QApplication>
#include <QtWidgets>

 
int main(int argc, char *argv[])  {
  // Creating the application object
  QApplication app(argc, argv);
  
  MainWindow w;
  w.show();
  
  // Running the application object
  return app.exec();
}