#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QNetworkAccessManager>


QT_BEGIN_NAMESPACE
namespace Ui { class MainUI; }
QT_END_NAMESPACE

class Controller;

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    MainUI(Controller *myController, QWidget *parent = nullptr);
    ~MainUI();

    void buttonToConnect();

    void buttonToForward();
    void buttonToBackward();
    void buttonToLeft();
    void buttonToRight();
    void buttonToStop();

    void constSpeed();

    void connected();
    void disconnected();

    void cameraMove(QString direction);
    void keyPressEvent(QKeyEvent *event);
    void setBattery(int battery);
    void setSpeed(QString speed);
    void setInfraRedFrontLeft(int IR);
    void setInfraRedFrontRight(int IR);
    void setInfraRedBackLeft(int IR);
    void setInfraRedBackRight(int IR);
    void setOdometry(QString speed);

private:
    Ui::MainUI *ui;
    Controller *myController;
    QNetworkAccessManager *Camera;
    QWebEngineView *webEngineView;
};

#endif // MAINUI_H
