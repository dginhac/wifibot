
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
}

