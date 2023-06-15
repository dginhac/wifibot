
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include "camera.h"
#include "controllerType.h"
#include "direction.h"

#include <QKeyEvent>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Camera* camera = new Camera(this);
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

//Gestion des différents controleur pour le déplacement du robot
void MainWindow::controlMoveRobot(ControllerType type, Direction direction, int speed) {
    //
}
void MainWindow::controlMoveRobotType(ControllerType type)
{
    //
}

//Mise à jour des capteur d'obstacle
void MainWindow::updateCaptor() {
    MyRobot* robot = new MyRobot();

    unsigned char irLF = (unsigned char)robot->DataToSend[3];
    unsigned char irLB = (unsigned char)robot->DataToSend[4];

    unsigned char irRF = (unsigned char)robot->DataToSend[11];
    unsigned char irRB = (unsigned char)robot->DataToSend[12];

    if (irLF >= 180) {
        ui->sensorFL->setText("100");
    }
    else {
        ui->sensorFL->setText(""+irLF * 100 / 180);
    }

    if (irRF >= 180) {
        ui->sensorFR->setText("100");
    }
    else {
        ui->sensorFR->setText(""+irRF * 100 / 180);
    }

    if (irLB >= 180) {
        ui->sensorBL->setText("100");
    }
    else {
        ui->sensorBL->setText(""+irLB * 100 / 180);
    }

    if (irRB >= 180) {
        ui->sensorBR->setText("100");
    }
    else {
        ui->sensorBR->setText(""+irRB * 100 / 180);
    }

    if (ui->sensorBL->text() == "100" || ui->sensorBR->text() == "100" || ui->sensorFL->text() == "100" || ui->sensorFL->text() == "100" || ui->sensorFR->text() == "100") {
        qDebug("Vibration");
    }
    else {

    }
}

//Pilotage du robot sur l'interface
void MainWindow::on_Avancer_pressed()
{
    bool ok;
    int speed = ui->speed->text().toInt(&ok);

    controlMoveRobot(ControllerType::INTERFACE, Direction::FORWARD, speed);
}


void MainWindow::on_Avancer_released()
{
    controlMoveRobotType(ControllerType::INTERFACE);
}


void MainWindow::on_Gauche_pressed()
{
    bool ok;
    int speed = ui->speed->text().toInt(&ok);

    controlMoveRobot(ControllerType::INTERFACE, Direction::LEFT, speed);
}

void MainWindow::on_Gauche_released()
{
    controlMoveRobotType(ControllerType::INTERFACE);
}

void MainWindow::on_Droite_pressed()
{
    controlMoveRobotType(ControllerType::INTERFACE);
}


void MainWindow::on_Droite_released()
{
    controlMoveRobotType(ControllerType::INTERFACE);
}


void MainWindow::on_Reculer_pressed()
{
    bool ok;
    int speed = ui->speed->text().toInt(&ok);

    controlMoveRobot(ControllerType::INTERFACE, Direction::BACKWARD, speed);
}

void MainWindow::on_Reculer_released()
{
    controlMoveRobotType(ControllerType::INTERFACE);
}

//Pilotage du robot avec les touches du clavier
void MainWindow::keyPressEvent(QKeyEvent *event){
    int touche = event->key();

    int speed = ui->speed->text().toInt();
    if (ui->speed->text().isEmpty()) {
        // Handle the case when the speed input is empty
        return;
    }

    switch(touche){

    case Qt::Key_Z:

        controlMoveRobot(ControllerType::INTERFACE, Direction::FORWARD, speed);
        break;

    case Qt::Key_Q:
        controlMoveRobot(ControllerType::INTERFACE, Direction::LEFT, speed);
        break;

    case Qt::Key_D:
        controlMoveRobot(ControllerType::INTERFACE, Direction::RIGHT, speed);
        break;

    case Qt::Key_S:
        controlMoveRobot(ControllerType::INTERFACE, Direction::BACKWARD, speed);
        break;
    }

}
