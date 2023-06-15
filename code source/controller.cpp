#include "controller.h"
#include <iostream>
#include <iomanip>
#include <QtMath>

// Constructor: Initializes the user interface and the robot, and connects the robot's updateUI signal to the controller's updateWindow slot.
Controller::Controller() : myUI(new MainUI(this)), myRobot(new MyRobot(this))
{
    connect(myRobot, SIGNAL(updateUI(QByteArray)), this, SLOT(updateWindow(QByteArray)));
}

// Destructor: Disconnects the robot before destroying the object.
Controller::~Controller() {
    this->myRobot->disConnect();
}

// Displays the user interface.
void Controller::showUI()
{
    this->myUI->show();
}

// Connects the robot to the controller.
void Controller::doConnect()
{
    this->myRobot->doConnect();
}

// Updates the user interface when the robot is connected.
void Controller::connected()
{
    this->myUI->connected();
}

// Updates the user interface when the robot is disconnected.
void Controller::disconnected()
{
    this->myUI->disconnected();
}

// Updates the user interface with new data received from the robot.
void Controller::updateWindow(QByteArray data)
{

}

