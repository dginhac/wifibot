#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller *myController = new Controller();
 
    myController->showUI();

    return a.exec();
}
