#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "myrobot.h"
#include "mainui.h"

class Controller : public QObject {
    Q_OBJECT
public:
    Controller();
    ~Controller();

    void showUI();
    void doConnect();
    void connected();
    void disconnected();

private slots:
    void updateWindow(QByteArray data);

private:
    MainUI *myUI;
    MyRobot *myRobot;

};

#endif // CONTROLLER_H
