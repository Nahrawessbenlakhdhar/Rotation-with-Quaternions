#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Object viewer");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_W_valueChanged(double arg1)
{
    qDebug()<<__func__;
   this->ui->GLwidget->w=arg1;
}


void MainWindow::on_x_valueChanged(double arg1)
{
    qDebug()<<__func__;
  this->ui->GLwidget->x=arg1;
}


void MainWindow::on_y_valueChanged(double arg1)
{
    qDebug()<<__func__;
  this->ui->GLwidget->y=arg1;
}


void MainWindow::on_z_valueChanged(double arg1)
{
    qDebug()<<__func__;
  this->ui->GLwidget->z=arg1;
}


//void MainWindow::on_pitch_valueChanged(double arg1)
//{
//    this->ui->GLwidget->pitch=arg1;
//}


//void MainWindow::on_yaw_valueChanged(double arg1)
//{
//    this->ui->GLwidget->yaw=arg1;
//}


//void MainWindow::on_roll_valueChanged(double arg1)
//{
//    this->ui->GLwidget->roll=arg1;
//}

