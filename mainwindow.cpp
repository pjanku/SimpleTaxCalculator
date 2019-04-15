#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->leWithoutTax, &QLineEdit::textChanged, this, &MainWindow::recalculate);
    connect(ui->rb15, &QRadioButton::clicked, this, &MainWindow::recalculate);
    connect(ui->rb21, &QRadioButton::clicked, this, &MainWindow::recalculate);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recalculate()
{
    bool success;
    double value = ui->leWithoutTax->text().toDouble(&success);
    if (success){
        if (ui->rb15->isChecked()){
            value *= 1.15;
        }else{
            value *= 1.21;
        }
        ui->leWithTax->setText(QString("%1").arg(value));
    }else ui->leWithTax->setText("N/A");
}

void MainWindow::on_pbClear_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this, tr("Ready to clear?"),"Do you really want to clear this form?")){
        ui->leWithTax->clear();
        ui->leWithoutTax->clear();
    }

}
