
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
    void on_connexion_button_clicked();

    void on_deconnexion_button_clicked();

    void updateSpeed();

    void updateBattery();

private:
    Ui::MainWindow *ui;
    long odometryLBefore = 0;
    long odometryRBefore = 0;
};

#endif // MAINWINDOW_H
