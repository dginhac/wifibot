#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class Controller;

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(Controller *myController, QObject *parent = 0);
    void doConnect();
    void disConnect();

    // Attributs publiques
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

signals:
    void updateUI(const QByteArray Data);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    Controller *myController;
};

#endif // MYROBOT_H
