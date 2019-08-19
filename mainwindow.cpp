#include "mainwindow.h"
#include <QPushButton>
#include <QColor>

MainWindow::MainWindow()
{
    setStyleSheet("background-color: darkblue;");
    poly_entry_form_layout = new QFormLayout;
    setLayout(poly_entry_form_layout);
    button_box_layout = new QBoxLayout(QBoxLayout::LeftToRight);
    button_grid_layout = new QGridLayout();
    poly_entry_form_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    // Labels and line edit objects for entering our polynomials
    poly_entry_label1.setText("Polynomial 1");
    poly_entry_label2.setText("Polynomial 2");
    poly_entry_label1.setStyleSheet("color: snow;");
    poly_entry_label2.setStyleSheet("color: snow;");
    poly_entry_box_1.setStyleSheet("color: snow;");
    poly_entry_box_2.setStyleSheet("color: snow;");
    // Qbutton objects for triggering subtract, addition, and scalar multiplication processes
    addition_button.setText("Add");
    subtraction_button.setText("Subtract");
    scalar_multiplication_button.setText("Scale");
    multiplication_button.setText("Multiply");

    addition_button.setStyleSheet("background-color: lightsteelblue; color: red;");
    subtraction_button.setStyleSheet("background-color: lightsteelblue; color: red;");
    scalar_multiplication_button.setStyleSheet("background-color: lightsteelblue; color: red;");
    multiplication_button.setStyleSheet("background-color: lightsteelblue; color: red;");

    button_box_layout->addWidget(&subtraction_button);
    button_box_layout->addWidget(&addition_button);
    button_box_layout->addWidget(&scalar_multiplication_button);
    button_box_layout->addWidget(&multiplication_button);

    poly_entry_form_layout->addRow(&poly_entry_label1, &poly_entry_box_1);
    poly_entry_form_layout->addRow(&poly_entry_label2, &poly_entry_box_2);
    poly_entry_form_layout->addRow(button_box_layout);
    poly_entry_form_layout->addRow(&result_display_box);
    result_display_box.setStyleSheet("color: snow;");

    connect(&addition_button,SIGNAL(clicked()),this,SLOT(onAdditionClicked()));
    connect(&subtraction_button,SIGNAL(clicked()),this,SLOT(onSubtractionClicked()));
    connect(&multiplication_button,SIGNAL(clicked()),this,SLOT(onMultiplicationClicked()));
}

void MainWindow::onAdditionClicked()
{
try{
        if (poly_entry_box_1.text() == "" || poly_entry_box_2.text() == "") throw "Nothing has been entered.";
        try{
            Polynomial p1(poly_entry_box_1.text().toUtf8().constData());
            Polynomial p2(poly_entry_box_2.text().toUtf8().constData());
            Polynomial sum(p1 + p2);

            result_display_box.setText("(" + p1.getQStr() + ")" + " + " + "(" + p2.getQStr() + ")\n= " + sum.getQStr());

        }catch (MalformedPolynomialException & mpe) {result_display_box.setText("Error formatting polynomials: " + QString::fromUtf8(mpe.what()));}

    }catch (...){result_display_box.setText("Nothing has been entered.\n");}

}

void MainWindow::onSubtractionClicked()
{
    try{
        Polynomial p1,p2,diff;
        try
        {
            p1 = Polynomial((poly_entry_box_1.text().toUtf8().constData()));
        }
        catch (MalformedPolynomialException & mpe)
        {
            result_display_box.setText("Error formatting polynomial 1: " + QString::fromUtf8(mpe.what()));
            poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid red");
            throw;
        }

        try
        {
            p2 = Polynomial(poly_entry_box_2.text().toUtf8().constData());
            diff = Polynomial(p1 - p2);
        } catch (MalformedPolynomialException & mpe)
        {
            result_display_box.setText("Error formatting polynomial 1: " + QString::fromUtf8(mpe.what()));
            poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid red");
            throw;
        }

        // Else if things were successful this time, get rid of the warning border
        poly_entry_box_1.setStyleSheet("color: snow;");
        poly_entry_box_2.setStyleSheet("color: snow;");
        result_display_box.setText("(" + p1.getQStr() + ")" + " - " + "(" + p2.getQStr() + ")\n= " + diff.getQStr());

    }catch (MalformedPolynomialException & mpe) {
        result_display_box.setText("Error formatting polynomials: " + QString::fromUtf8(mpe.what()));}

}

void MainWindow::onMultiplicationClicked()
{
    try{
        Polynomial p1(poly_entry_box_1.text().toUtf8().constData());
        Polynomial p2(poly_entry_box_2.text().toUtf8().constData());
        Polynomial product(p1.dot(p2));

        result_display_box.setText("(" + p1.getQStr() + ")" + " * " + "(" + p2.getQStr() + ")\n= " + product.getQStr());

    }catch (MalformedPolynomialException & mpe) {result_display_box.setText("Error formatting polynomials: " + QString::fromUtf8(mpe.what()));}


}
