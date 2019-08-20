#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QWidget>
#include "polynomial.h"
#include <sstream>
#include <QGridLayout>
#include <QHBoxLayout>

class MainWindow : public QWidget
{
    Q_OBJECT
public:

    MainWindow();
private slots:
    void onAdditionClicked();
    void onSubtractionClicked();
    void onMultiplicationClicked();
    void onEvaluateClicked();
private:
       QFormLayout * poly_entry_form_layout;
       QBoxLayout * button_box_layout;
       QHBoxLayout * value_evaluation_layout;
       QGridLayout * button_grid_layout;
       QTextBrowser result_display_box;
       QLabel poly_entry_label1, poly_entry_label2, enter_xvalue_label, evaluation_display_box;
       QLineEdit poly_entry_box_1, poly_entry_box_2, xvalue_entry_box;
       QPushButton subtraction_button, addition_button, evaluation_button, multiplication_button;

       Polynomial current_result;

};



#endif // MAINWINDOW_H
