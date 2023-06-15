#include "mainui.h"
#include "controller.h"
#include "ui_mainui.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QKeyEvent>
#include <QHBoxLayout>

// Constructor: Initializes the MainUI with the given controller and parent widget.
// Sets up the user interface and connects the signals to the corresponding slots.
MainUI::MainUI(Controller *myController, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
    , myController(myController)
    , Camera(new QNetworkAccessManager())
{
    ui->setupUi(this);

    connect(ui->buttonConnect, &QPushButton::clicked, this, &MainUI::buttonToConnect);

    connect(ui->upButton, &QPushButton::clicked, this, &MainUI::buttonToForward);
    connect(ui->downButton, &QPushButton::clicked, this, &MainUI::buttonToBackward);
    connect(ui->leftButton, &QPushButton::clicked, this, &MainUI::buttonToLeft);
    connect(ui->rightButton, &QPushButton::clicked, this, &MainUI::buttonToRight);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainUI::buttonToStop);
}

// Destructor: Cleans up allocated resources.
MainUI::~MainUI()
{
    delete ui;
}

// Calls the doConnect() method of the associated controller to initiate the connection.
void MainUI::buttonToConnect()
{
    this->myController->doConnect();
}

// Calls the goForward() method of the associated controller to move forward.
void MainUI::buttonToForward()
{
    myController->goForward();
}

// Calls the goBackward() method of the associated controller to move backward.
void MainUI::buttonToBackward()
{
    myController->goBackward();
}

// Calls the goLeft() method of the associated controller to turn left.
void MainUI::buttonToLeft()
{
    myController->goLeft();
}

// Calls the goRight() method of the associated controller to turn right.
void MainUI::buttonToRight()
{
    myController->goRight();
}

// Calls the goStop() method of the associated controller to stop movement.
void MainUI::buttonToStop()
{
    myController->goStop();
}


// Updates the UI to show the connected state and changes the button text.
void MainUI::connected()
{
    ui->buttonConnect->setText("DECONNEXION");
}

// Updates the UI to show the disconnected state and changes the button text.
void MainUI::disconnected()
{
    ui->buttonConnect->setText("CONNEXION");
}

// Event handler: Processes key press events and calls the corresponding controller methods.
void MainUI::keyPressEvent(QKeyEvent *event){
    int touche = event->key();
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    switch(touche){

    case Qt::Key_Z:
        myController->goForward();
        break;

    case Qt::Key_Q:
        myController->goLeft();
        break;

    case Qt::Key_D:
        myController->goRight();
        break;

    case Qt::Key_S:
        myController->goBackward();
        break;

    case Qt::Key_A:
        myController->goStop();
        break;

    case Qt::Key_Up:
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
        break;

    case Qt::Key_Right:
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
        break;

    case Qt::Key_Down:
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
        break;

    case Qt::Key_Left:
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
        break;

    }

}

// Updates the battery level progress bar with the given battery value.
void MainUI::setBattery(int battery)
{
    ui->progressBar->setValue(battery);
}

// Updates the back left infrared sensor progress bar with the given IR value.
void MainUI::setInfraRedBackLeft(int IR)
{
    ui->progressBar_BackLeft->setValue(IR);
}


// Displays the given odometry value.
void MainUI::setOdometry(QString strOdometry) {
    ui->odometryLabel->setText(strOdometry);
}

// Updates the back right infrared sensor progress bar with the given IR value.
void MainUI::setInfraRedBackRight(int IR)
{
    ui->progressBar_BackRight->setValue(IR);
}

// Updates the front left infrared sensor progress bar with the given IR value.
void MainUI::setInfraRedFrontLeft(int IR)
{
    ui->progressBar_FrontLeft->setValue(IR);
}

// Updates the front right infrared sensor progress bar with the given IR value.
void MainUI::setInfraRedFrontRight(int IR)
{
    ui->progressBar_FrontRight->setValue(IR);
}

