#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

#include "direction.h"

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    bool doConnect();
    void disConnect();

    QByteArray DataToSend;
    QByteArray DataReceived;

    QMutex Mutex;

    bool const isConnect();

signals:
    void updateUI(const QByteArray Data);

public slots:
    void connected();
    void disconnected();

    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

    void move(Direction direction = Direction::NONE, quint8 Velocity = 0x00);
    void GetData();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;

    quint16 crc16(QByteArray adresseTab, unsigned int tailleMax);

    bool _isConnect = false;
};

#endif // MYROBOT_H
