
#include <QApplication>
#include <QtGui>
#include "mainwindow.h"
void handleAddition(){};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Declare a layout type, declare relevant widgets which will compose the layout, and assign these widgets to the layout
    // QFormLayout takse a pointer to a widget as its argument to determine its location

    MainWindow main_window;
    // Declare, size, show, and title your window

    main_window.resize(250,95);
    main_window.show();
    main_window.setWindowTitle("Polynomial Calculator");

    return a.exec();
}
