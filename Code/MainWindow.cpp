#include "mainwindow.h"
/*
 Useless class. Saving for historical reasons.

 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
 //   int height = floor(GetSystemMetrics(SM_CXSCREEN)/2); // let's not make it full screen....
   // int width = floor(GetSystemMetrics(SM_CYSCREEN)/2);


   // cout << "We have " << height << " " << width;
    w = new ConfigWizard;


    setFont(QFont("Verdana", 9));
  //  resize(0, 0);
    move(0,0);

}

MainWindow::~MainWindow()
{
    //delete ui;
}
