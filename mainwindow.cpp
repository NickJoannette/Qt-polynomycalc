#include "mainwindow.h"
#include <QPushButton>
#include <QColor>

MainWindow::MainWindow()
{

    // Setting up layouts and main stylesheet
    setStyleSheet("background-color: 	#2a4d69;");
    poly_entry_form_layout = new QFormLayout;
    setLayout(poly_entry_form_layout);
    button_box_layout = new QBoxLayout(QBoxLayout::LeftToRight);
    button_grid_layout = new QGridLayout();
    value_evaluation_layout = new QHBoxLayout();
    poly_entry_form_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    // Stylesheet, text, and attribute setting for child widgets
    poly_entry_label1.setText("Polynomial 1");
    poly_entry_label2.setText("Polynomial 2");
    enter_xvalue_label.setText("Value of x:");
    enter_xvalue_label.setStyleSheet("color: #e7eff6;");
    poly_entry_label1.setStyleSheet("color: #e7eff6;");
    poly_entry_label2.setStyleSheet("color: #e7eff6;");
    poly_entry_box_1.setStyleSheet("color: #e7eff6;");
    poly_entry_box_2.setStyleSheet("color: #e7eff6;");
    xvalue_entry_box.setStyleSheet("color: #e7eff6;");
    result_display_box.setStyleSheet("color: #e7eff6; border: 1px outset #4b86b4;");
    evaluation_display_box.setStyleSheet("color: #e7eff6; border: 1px outset #4b86b4;");
    evaluation_display_box.setMinimumWidth(80);

    // Qbutton objects for triggering subtract, addition, and scalar multiplication processes
    addition_button.setText("Add");
    subtraction_button.setText("Subtract");
    evaluation_button.setText("Evaluate");
    multiplication_button.setText("Multiply");


    addition_button.setStyleSheet("padding: 5px; background-color: #101e2a; color: #e7eff6; border: 1px ridge ivory;");
    subtraction_button.setStyleSheet("padding: 5px; background-color: #101e2a; color: #e7eff6;border: 1px ridge ivory;");
    evaluation_button.setStyleSheet("padding: 5px; background-color: #101e2a; color: #e7eff6;border: 1px ridge ivory;");
    multiplication_button.setStyleSheet("padding: 5px; background-color: #101e2a; color: #e7eff6;border: 1px ridge ivory;");

    button_box_layout->addWidget(&subtraction_button);
    button_box_layout->addWidget(&addition_button);
    button_box_layout->addWidget(&multiplication_button);

    value_evaluation_layout->addWidget(&enter_xvalue_label);
    value_evaluation_layout->addWidget(&xvalue_entry_box);
    value_evaluation_layout->addWidget(&evaluation_button);
    value_evaluation_layout->addWidget(&evaluation_display_box);

    poly_entry_form_layout->addRow(&poly_entry_label1, &poly_entry_box_1);
    poly_entry_form_layout->addRow(&poly_entry_label2, &poly_entry_box_2);
    poly_entry_form_layout->addRow(button_box_layout);
    poly_entry_form_layout->addRow(&result_display_box);
    poly_entry_form_layout->addRow(value_evaluation_layout);



    connect(&addition_button,SIGNAL(clicked()),this,SLOT(onAdditionClicked()));
    connect(&subtraction_button,SIGNAL(clicked()),this,SLOT(onSubtractionClicked()));
    connect(&multiplication_button,SIGNAL(clicked()),this,SLOT(onMultiplicationClicked()));
    connect(&evaluation_button,SIGNAL(clicked()),this,SLOT(onEvaluateClicked()));
}

void MainWindow::onAdditionClicked()
{

      if (poly_entry_box_1.text() == "") poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
      else poly_entry_box_1.setStyleSheet("color: snow;");

      if (poly_entry_box_2.text() == "")poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
      else poly_entry_box_2.setStyleSheet("color: snow;");

      if (!(poly_entry_box_1.text() == "" || poly_entry_box_2.text() == ""))
        try{
            Polynomial p1,p2,sum;
            try
            {
                p1 = Polynomial((poly_entry_box_1.text().toUtf8().constData()));
            }
            catch (MalformedPolynomialException & mpe)
            {
                result_display_box.setText("Error formatting polynomial 1: " + QString::fromUtf8(mpe.what()));
                poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");

                    try
                    {
                        p2 = Polynomial(poly_entry_box_2.text().toUtf8().constData());
                    } catch (MalformedPolynomialException & mpe)
                    {
                        poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                    }

                throw;
            }

            try
            {
                p2 = Polynomial(poly_entry_box_2.text().toUtf8().constData());
                sum = Polynomial(p1 + p2);
            } catch (MalformedPolynomialException & mpe)
            {
                result_display_box.setText("Error formatting polynomial 1: " + QString::fromUtf8(mpe.what()));
                poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                    try
                    {
                        p1 = Polynomial((poly_entry_box_1.text().toUtf8().constData()));
                    }
                    catch (MalformedPolynomialException & mpe)
                    {
                        poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                    }

                throw;
            }

            current_result = sum;
            result_display_box.setText("(" + p1.getQStr() + ")" + " + " + "(" + p2.getQStr() + ")\n= " + sum.getQStr());

        }catch (MalformedPolynomialException & mpe) {result_display_box.setText("Error formatting polynomials: " + QString::fromUtf8(mpe.what()));}

}

void MainWindow::onSubtractionClicked()
{

        if (poly_entry_box_1.text() == "") poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
        else poly_entry_box_1.setStyleSheet("color: snow;");

        if (poly_entry_box_2.text() == "")poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
        else poly_entry_box_2.setStyleSheet("color: snow;");

        if (!(poly_entry_box_1.text() == "" || poly_entry_box_2.text() == ""))
        try{
                Polynomial p1,p2,diff;
                try
                {
                    p1 = Polynomial((poly_entry_box_1.text().toUtf8().constData()));
                }
                catch (MalformedPolynomialException & mpe)
                {
                    result_display_box.setText("Error formatting polynomial 1: " + QString::fromUtf8(mpe.what()));
                    poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                        try
                        {
                            p2 = Polynomial(poly_entry_box_2.text().toUtf8().constData());
                        } catch (MalformedPolynomialException & mpe)
                        {
                            poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                        }

                    throw;
                }

                try
                {
                    p2 = Polynomial(poly_entry_box_2.text().toUtf8().constData());
                    diff = Polynomial(p1 - p2);
                } catch (MalformedPolynomialException & mpe)
                {
                    result_display_box.setText("Error formatting polynomial 1: " + QString::fromUtf8(mpe.what()));
                    poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                        try
                        {
                            p1 = Polynomial((poly_entry_box_1.text().toUtf8().constData()));
                        }
                        catch (MalformedPolynomialException & mpe)
                        {
                            poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                        }
                    throw;
                }

                // Else if things were successful this time, get rid of the warning border
                poly_entry_box_1.setStyleSheet("color: snow;");
                poly_entry_box_2.setStyleSheet("color: snow;");
                current_result = diff;
                result_display_box.setText("(" + p1.getQStr() + ")" + " - " + "(" + p2.getQStr() + ")\n= " + (diff.terms.size() > 0 ? diff.getQStr() : "0"));

           }catch (MalformedPolynomialException & mpe) {result_display_box.setText("Error formatting polynomials: " + QString::fromUtf8(mpe.what()));}

}

void MainWindow::onMultiplicationClicked()
{

        if (poly_entry_box_1.text() == "") poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
        else poly_entry_box_1.setStyleSheet("color: snow;");

        if (poly_entry_box_2.text() == "")poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
        else poly_entry_box_2.setStyleSheet("color: snow;");
        if (!(poly_entry_box_1.text() == "" || poly_entry_box_2.text() == ""))
        try{
                Polynomial p1,p2,product;
                try
                {
                    p1 = Polynomial((poly_entry_box_1.text().toUtf8().constData()));
                }
                catch (MalformedPolynomialException & mpe)
                {
                    result_display_box.setText("Error formatting polynomial: " + QString::fromUtf8(mpe.what()));
                    poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                            try
                            {
                                p2 = Polynomial(poly_entry_box_2.text().toUtf8().constData());
                                product = Polynomial(p1.dot(p2));
                            } catch (MalformedPolynomialException & mpe)
                            {
                                 poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");
                            }

                    throw;
                }

                try
                {
                    p2 = Polynomial(poly_entry_box_2.text().toUtf8().constData());
                    product = Polynomial(p1.dot(p2));
                } catch (MalformedPolynomialException & mpe)
                {
                    result_display_box.setText("Error formatting polynomial: " + QString::fromUtf8(mpe.what()));
                    poly_entry_box_2.setStyleSheet("color: snow; border: 2px solid #CD3C3C");

                            try
                            {
                                p1 = Polynomial((poly_entry_box_1.text().toUtf8().constData()));
                            }
                            catch (MalformedPolynomialException & mpe)
                            {
                                 poly_entry_box_1.setStyleSheet("color: snow; border: 2px solid #CD3C3C");

                            }

                    throw;
                }

                // Else if things were successful this time, get rid of the warning border
                poly_entry_box_1.setStyleSheet("color: snow;");
                poly_entry_box_2.setStyleSheet("color: snow;");
                current_result = product;
                result_display_box.setText("(" + p1.getQStr() + ")" + " * " + "(" + p2.getQStr() + ")\n= " + product.getQStr());

           }catch (MalformedPolynomialException & mpe) {result_display_box.setText("Error formatting polynomials: " + QString::fromUtf8(mpe.what()));}



}

void MainWindow::onEvaluateClicked()
{
    double value_of_x = xvalue_entry_box.text().toDouble();
    evaluation_display_box.setText(QString::number(current_result(value_of_x)));


}
