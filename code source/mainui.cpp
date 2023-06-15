#include "mainui.h"
#include "controller.h"
#include "ui_mainui.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QKeyEvent>
#include <QHBoxLayout>

// Constructor: Initializes the MainUI with the given controller and parent widget.
// Sets up the user interface and connects the signals to the corresponding slots.
MainUI::MainUI(QWidget *parent, MainUI *ui)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);

    connect(ui->buttonConnect, &QPushButton::clicked, this, &MainUI::buttonToConnect);
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

