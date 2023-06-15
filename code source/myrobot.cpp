#include "myrobot.h"
#include "controller.h"


// Constructor: Initializes a MyRobot object with the provided Controller, sets up the DataToSend and DataReceived arrays, and creates a QTimer for data transmission.
MyRobot::MyRobot(Controller *myController, QObject *parent) : QObject(parent), myController(myController) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}

// Establishes a connection with the wifibot and starts the data transmission timer.
void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    socket->connectToHost("192.168.1.106", 15020);
    //socket->connectToHost("192.168.10.1", 5002); // connection to wifibot
    // we need to wait...
    emit connected();
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);
}

// Disconnects from the wifibot and stops the data transmission timer.
void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

// Slot called when the robot is connected, emits a signal to the controller.
void MyRobot::connected() {
    qDebug() << "connected...";
    this->myController->connected();
}

// Slot called when the robot is disconnected, emits a signal to the controller.
void MyRobot::disconnected() {
    qDebug() << "disconnected...";
    this->myController->disconnected();
}

// Slot called when the robot has written data to the socket, logs the number of bytes written.
void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

// Slot called when there is data available to read from the socket, reads the data and emits a signal to update the UI.
void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
}

// Timer slot: Sends the DataToSend array to the wifibot over the socket at regular intervals.
void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}
