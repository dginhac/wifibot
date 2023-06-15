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

    void connected();
    void disconnected();

private:
    Ui::MainUI *ui;
    Controller *myController;
};

#endif // MAINUI_H
