#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_W_valueChanged(double arg1);

    void on_x_valueChanged(double arg1);

    void on_y_valueChanged(double arg1);

    void on_z_valueChanged(double arg1);

    void on_a_valueChanged(double arg1);

    void on_pitch_valueChanged(double arg1);

    void on_yaw_valueChanged(double arg1);

    void on_roll_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
