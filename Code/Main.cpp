#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include <windows.h>
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//   MainWindow w;

    a.libraryPaths();

    ConfigWizard w;
    w.setWindowIcon(QIcon("Logo_small.png"));
    w.adjustSize();
    w.move(0,0);
    w.show();

    return a.exec();
}

