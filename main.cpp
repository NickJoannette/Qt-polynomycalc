
#include <QApplication>
#include <QtGui>
#include "mainwindow.h"

void handleAddition(){};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.show();
    main_window.setWindowTitle("Polynomial Calculator");
    return a.exec();
}
