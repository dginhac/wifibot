
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


