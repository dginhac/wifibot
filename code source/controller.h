#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "myrobot.h"
#include "mainui.h"

class Controller : public QObject {
    Q_OBJECT
public:
    Controller();
    ~Controller();

    short crc16(char *adresseTab, unsigned char tailleMax);

    void showUI();
    void doConnect();
    void connected();
    void disconnected();

    void goForward();
    void goBackward();
    void goLeft();
    void goRight();
    void goStop();

    void updateBattery(QByteArray dataToUpdate);
    void updateOdometry(QByteArray dataToUpdate);

    long parseLong(const QByteArray& data, int startIndex);

private slots:
    void updateWindow(QByteArray data);

private:
    MainUI *myUI;
    MyRobot *myRobot;

};

#endif // CONTROLLER_H
