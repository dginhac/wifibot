
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connexion_button_clicked()
{
    MyRobot* robot = new MyRobot();
    robot->doConnect();
    updateBattery();
    updateSpeed();
    robot->move(Direction::FORWARD_LEFT, 128);
}


void MainWindow::on_deconnexion_button_clicked()
{
    MyRobot* robot = new MyRobot();
    robot->disConnect();
}



void MainWindow::updateBattery()
{
    MyRobot* robot = new MyRobot();

    unsigned char battery = (unsigned char)robot->DataReceived[2];
    if(battery > 170) {
        //ui->label_6->setText("En charge");
    }
    else {
        ui->Batterie_bar->setValue(battery * 100 / 123);
    }
}

void MainWindow::updateSpeed()
{
    MyRobot* robot = new MyRobot();

    long odometryL = ((long)robot->DataReceived[8]<<24)+((long)robot->DataReceived[7]<<16)+((long)robot->DataReceived[6]<<8)+((long)robot->DataReceived[5]);
    long odometryR = ((long)robot->DataReceived[16]<<24)+((long)robot->DataReceived[15]<<16)+((long)robot->DataReceived[14]<<8)+((long)robot->DataReceived[13]);
    double odometryLBefore = 0.0;

    double speedL;
    if (odometryLBefore<odometryL) {
        speedL = (odometryL - odometryLBefore) * 3.14 * 0.135 / 0.025;
        odometryLBefore = odometryL;
    }
    else {
        speedL = (0xFFFFFFFF-odometryLBefore + odometryL) * 3.14 * 0.135 / 0.025;
        odometryLBefore = odometryL;
    }

    double speedR;
    if (odometryRBefore<odometryR) {
        speedR = (odometryR - odometryRBefore) * 3.14 * 0.135 / 0.025;
        odometryRBefore = odometryR;
    }
    else {
        speedR = (0xFFFFFFFF-odometryRBefore + odometryR) * 3.14 * 0.135 / 0.025;
        odometryRBefore = odometryR;
    }

    double speed = (speedL + speedR) / 20000;


    if (speed > 1000000)
        speed = 0;

    QString textSpeed = QString::number(speed) + " m/s";
    ui->speed->setText(textSpeed);
    //qDebug() << "Speed: " << speed;
}
