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

// Computes the 16-bit CRC for a given data buffer and its size.
short Controller::crc16(char *adresseTab, unsigned char tailleMax)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 1;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;

    Polynome = 0xA001;
    for ( CptOctet= 1 ; CptOctet < tailleMax ; CptOctet++)
    {
        Crc ^= *( adresseTab + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
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

// Sends a command to the robot to move forward.
void Controller::goForward()
{
    this->myRobot->DataToSend[2] = 90; // default speed
    this->myRobot->DataToSend[3] = 0;
    this->myRobot->DataToSend[4] = 90; // default speed
    this->myRobot->DataToSend[5] = 0;
    this->myRobot->DataToSend[6] = 80;

    short CRC = this->crc16(this->myRobot->DataToSend.data(), 7);

    this->myRobot->DataToSend[7] = CRC;
    this->myRobot->DataToSend[8] = CRC >> 8;

    qDebug() << this->myRobot->DataToSend;
}

// Sends a command to the robot to move backward.
void Controller::goBackward()
{
    this->myRobot->DataToSend[2] = 120; // default speed
    this->myRobot->DataToSend[3] = 0;
    this->myRobot->DataToSend[4] = 120; // default speed
    this->myRobot->DataToSend[5] = 0;
    this->myRobot->DataToSend[6] = 0;

    short CRC = this->crc16(this->myRobot->DataToSend.data(), 7);

    this->myRobot->DataToSend[7] = CRC;
    this->myRobot->DataToSend[8] = CRC >> 8;
}

// Sends a command to the robot to turn left.
void Controller::goLeft()
{
    this->myRobot->DataToSend[2] = 0;
    this->myRobot->DataToSend[3] = 0;
    this->myRobot->DataToSend[4] = 120; // default speed
    this->myRobot->DataToSend[5] = 0;
    this->myRobot->DataToSend[6] = 64;

    short CRC = this->crc16(this->myRobot->DataToSend.data(), 7);

    this->myRobot->DataToSend[7] = CRC;
    this->myRobot->DataToSend[8] = CRC >> 8;
}

// Sends a command to the robot to turn right.
void Controller::goRight()
{
    this->myRobot->DataToSend[2] = 120; // default speed
    this->myRobot->DataToSend[3] = 0;
    this->myRobot->DataToSend[4] = 0;
    this->myRobot->DataToSend[5] = 0;
    this->myRobot->DataToSend[6] = 16;

    short CRC = this->crc16(this->myRobot->DataToSend.data(), 7);

    this->myRobot->DataToSend[7] = CRC;
    this->myRobot->DataToSend[8] = CRC >> 8;
}

// Sends a command to the robot to stop moving.
void Controller::goStop()
{
    this->myRobot->DataToSend[2] = 0;
    this->myRobot->DataToSend[3] = 0;
    this->myRobot->DataToSend[4] = 0;
    this->myRobot->DataToSend[5] = 0;
    this->myRobot->DataToSend[6] = 0;

    short CRC = this->crc16(this->myRobot->DataToSend.data(), 7);

    this->myRobot->DataToSend[7] = CRC;
    this->myRobot->DataToSend[8] = CRC >> 8;
}

// Updates the user interface with new data received from the robot.
void Controller::updateWindow(QByteArray data)
{
    updateBattery(data);
    updateOdometry(data);
}

// Updates the battery level information in the user interface.
void Controller::updateBattery(QByteArray dataToUpdate)
{
    unsigned char battery = (unsigned char)dataToUpdate[2];

    if(battery > 170)
        myUI->setBattery(100);
    else
        myUI->setBattery(battery * 100 / 123);
}


// Updates the odometry captor values in the user interface.
void Controller::updateOdometry(QByteArray data) {
    // Extract the odometry values from the received data
    long odometryL = parseLong(data, 5);
    long odometryR = parseLong(data, 13);

    // Create a string representation of the odometry values
    QString odometryText = QString::number(odometryL) + ", " + QString::number(odometryR);

    // Call the UI's method to update the displayed odometry
    myUI->setOdometry(odometryText);
}


// Extract four bytes from the data and combine them into a long value
long Controller::parseLong(const QByteArray& data, int startIndex) {
    return ((long)data[startIndex + 3] << 24) +
           ((long)data[startIndex + 2] << 16) +
           ((long)data[startIndex + 1] << 8) +
           ((long)data[startIndex]);
}
