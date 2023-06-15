
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controllerType.h>
#include "direction.h"



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

    void updateCaptor();

    void on_Avancer_pressed();

    void on_Avancer_released();

    void on_Gauche_pressed();

    void on_Gauche_released();

    void on_Droite_pressed();

    void on_Droite_released();

    void on_Reculer_pressed();

    void on_Reculer_released();


private:
    Ui::MainWindow *ui;
    long odometryLBefore = 0;
    long odometryRBefore = 0;

    double axisLeftX;
    double axisLeftY;
    bool allAxisLeft = false;

    double axisRightX;
    double axisRightY;
    bool allAxisRight = false;

    Direction toDirectionRobot(double x, double y);
    void controlMoveRobot(ControllerType type, Direction direction, int speed);

    void controlMoveRobotType(ControllerType type);


    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
